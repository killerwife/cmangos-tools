// EAIExpander.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <set>
#include <vector>

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/exception.h>
#include <jdbc/cppconn/resultset.h>
#include <jdbc/cppconn/prepared_statement.h>

#define TARGET_HOST "localhost:2045"
#define TARGET_USER "root"
#define TARGET_PASS "deadlydeath"
#define TARGET_DB "wotlkmangos"

// #define TABLENAME "`creature_ai_scripts`"
// #define TABLENAME "`creature_ai_texts`"
#define TABLENAME "script_texts"

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
    if (line[0] == '-' && line[1] == '-')
        return false;
    long ids[2];
    ids[0] = 0;
    ids[1] = -1;
    std::string outputLine = "";
    bool readingNum = false;
    int idCount = 0;
    int curNum = 0;
    bool sign = false;
    for (int i = 0; i < line.size(); ++i)
    {
        if (readingNum)
        {
            if (line[i] == '-')
                sign = true;
            if (line[i] >= '0' && line[i] <= '9')
            {
                curNum = curNum * 10 + line[i] - '0';
            }
            // else if (line[i] == '\'') -- EAI file
            else if (line[i] == ',')
            {
                if (sign)
                    curNum = -curNum;
                ids[idCount++] = curNum;
                readingNum = false;
                curNum = 0;
                //if (idCount == 2) -- creature_ai_scripts
                if (idCount == 1)
                    break;
            }
        }
        // else if (line[i] == '\'') -- EAI file
        else if (line[i] == '(')
            readingNum = true;
    }
    // if (ids[0] != -1 && ids[1] != -1) - creature_ai_scripts
    if (ids[0] != 0)
    {
        if (foundIds.find(ids[0]) != foundIds.end())
            return true;
        // std::string statement = "SELECT * FROM creature_ai_scripts WHERE id = " + std::to_string(ids[0]) + " AND creature_id = " + std::to_string(ids[1]) + "";
        std::string statement = "SELECT entry,content_default,sound,type,language,emote,broadcast_text_id,comment FROM " TABLENAME " WHERE entry = " + std::to_string(ids[0]) + "";
        std::unique_ptr<sql::ResultSet> result(stmt->executeQuery(statement));
        sql::ResultSetMetaData* meta = result->getMetaData();
        while (result->next())
        {
            outputLine += "(";
            for (unsigned int i = 1; i <= meta->getColumnCount(); ++i)
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
                for (size_t i = line.size() - 1; i >= 0; ++i)
                {
                    if (line[i] == ';') // only last character in a line
                        processLine = false;
                    else if (line[i] != ' ')
                        break;
                }
                lineProcessed = ProcessLine(line, outputFile, stmt, !processLine);
            }
            // else if (line.find("INSERT INTO `creature_ai_scripts`") != std::string::npos)
            else if (line.find("INSERT INTO " TABLENAME) != std::string::npos)
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

