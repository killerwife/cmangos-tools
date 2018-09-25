// EAIExpander.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

#define TARGET_HOST "localhost:2045"
#define TARGET_USER "root"
#define TARGET_PASS "deadlydeath"
#define TARGET_DB "wotlkmangos"

std::set<long> foundIds;

std::string escapeString(std::string string)
{
    std::string output;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == '\'')
            output += "'";
        output += string[i];
    }
    return output;
}

bool ProcessLine(std::string& line, std::ofstream& outputFile, std::auto_ptr<sql::Statement>& stmt, bool end)
{
    long ids[2];
    ids[0] = -1;
    ids[1] = -1;
    std::string outputLine = "";
    bool readingNum = false;
    int idCount = 0;
    int curNum = 0;
    for (int i = 0; i < line.size(); ++i)
    {
        if (readingNum)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                curNum = curNum * 10 + line[i] - '0';
            }
            else if (line[i] == '\'')
            {
                ids[idCount++] = curNum;
                readingNum = false;
                curNum = 0;
                if (idCount == 2)
                    break;
            }
        }
        else if (line[i] == '\'')
            readingNum = true;
    }
    if (ids[0] != -1 && ids[1] != -1)
    {
        if (foundIds.find(ids[1]) != foundIds.end())
            return true;
        std::string statement = "SELECT * FROM creature_ai_scripts WHERE id = " + std::to_string(ids[0]) + " AND creature_id = " + std::to_string(ids[1]) + "";
        std::unique_ptr<sql::ResultSet> result(stmt->executeQuery(statement));
        sql::ResultSetMetaData* meta = result->getMetaData();
        while (result->next())
        {
            outputLine += "(";
            for (int i = 1; i <= meta->getColumnCount(); ++i)
            {
                if (i != 1)
                    outputLine += ",";
                outputLine += "\'" + escapeString(result->getString(i)) + "\'";
            }
            if (end)
                outputLine += ");\n";
            else
                outputLine += "),\n";
        }
    }
    else return false;
    outputFile << outputLine;
    return true;
}

int main()
{
    std::ifstream inputConfig;
    inputConfig.open("config.txt");
    std::string inputFileName;
    std::string outputFileName;
    std::getline(inputConfig, inputFileName);
    std::getline(inputConfig, outputFileName);
    std::ifstream inputFile;
    std::ofstream outputFile;
    inputFile.open(inputFileName);
    outputFile.open(outputFileName);
    std::string line;
    bool processLine = false;

    std::string url;
    std::string user;
    std::string pass;
    std::string database;
    std::getline(inputConfig, url);
    std::getline(inputConfig, user);
    std::getline(inputConfig, pass);
    std::getline(inputConfig, database);
    try
    {
        sql::Driver* driver = get_driver_instance();
        std::auto_ptr<sql::Connection> con(driver->connect(url, user, pass));
        con->setSchema(database);
        std::auto_ptr<sql::Statement> stmt(con->createStatement());
        std::vector<std::string> linesForProcessing;
        while (std::getline(inputFile, line))
        {
            bool lineProcessed = false;
            if (processLine)
            {
                for (int i = line.size() - 1; i >= 0; ++i)
                {
                    if (line[i] == ';') // only last character in a line
                        processLine = false;
                    else if (line[i] != ' ')
                        break;
                }
                lineProcessed = ProcessLine(line, outputFile, stmt, !processLine);
            }
            else if (line.find("INSERT INTO `creature_ai_scripts`") != std::string::npos)
                processLine = true;

            if (!lineProcessed)
                outputFile << line << std::endl;
        }
    }
    catch (sql::SQLException &e) {
        /*
        MySQL Connector/C++ throws three different exceptions:

        - sql::MethodNotImplementedException (derived from sql::SQLException)
        - sql::InvalidArgumentException (derived from sql::SQLException)
        - sql::SQLException (derived from std::runtime_error)
        */
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
        /* what() (derived from std::runtime_error) fetches error message */
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;

        return -1;
    }
    return 0;
}

