// SpellXMLParser.cpp : Defines the entry point for the console application.
//

#include <stdexcept>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define EXAMPLE_HOST "localhost:2045"
#define EXAMPLE_USER "root"
#define EXAMPLE_PASS "deadlydeath"
#define EXAMPLE_DB "spelldbc"

#define PATH "C:\\GitHubCode\\SpellsFromXMLBlizzard\\Release"

void GetFileNames(std::string& path, std::vector<std::string>& filenames)
{
    std::string temp = path + "\\*.*";
    std::wstring stemp = std::wstring(temp.begin(), temp.end());
    LPCWSTR sw = stemp.c_str();
    HANDLE hFind;
    WIN32_FIND_DATA data;
    hFind = FindFirstFile(sw, &data);
    int i = 0;
    if (hFind != INVALID_HANDLE_VALUE) {
        do {
            if (i >= 2) // skip . and ..
            {
                stemp = data.cFileName;
                filenames.push_back(std::string(stemp.begin(), stemp.end()));
            }
            i++;
        } while (FindNextFile(hFind, &data));
        FindClose(hFind);
    }
}

struct DBData
{
    uint32_t id;
    std::string name;
    std::string description;
};

std::vector<DBData> dbData;

void escapeString(std::string& string)
{
    std::string output;
    for (int i = 0; i < string.size(); i++)
    {
        if (string[i] == '\'')
            output += "'";
        output += string[i];
    }
    string = output;
}

void SaveToDB()
{
    std::string url(EXAMPLE_HOST);
    const std::string user(EXAMPLE_USER);
    const std::string pass(EXAMPLE_PASS);
    const std::string database(EXAMPLE_DB);
    try {

        sql::Driver* driver = get_driver_instance();
        if (!driver)
            printf("Bla");
        auto variable = driver->connect(url, user, pass);
        std::unique_ptr<sql::Connection> con(variable);
        con->setSchema(database);
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        for (auto& data : dbData)
        {
            escapeString(data.name);
            escapeString(data.description);
            std::string outputString = "INSERT INTO spellXML(Id,SpellName,Description) VALUES(" + std::to_string(data.id) + ",'" + data.name + "','" + data.description + "')";
            // printf("%s\n",outputString.data());
            stmt->execute(outputString);
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

        return;
    }

    std::cout << "Done." << std::endl;
}

void FillData()
{
    std::string path(PATH);
    std::vector<std::string> filenames;
    GetFileNames(path, filenames);

    for (std::string& filename : filenames)
    {
        std::ifstream myfile;
        std::string path(std::string(PATH) + '\\' + filename);
        myfile.open(path);
        DBData data;
        data.id = std::atol(filename.data());
        data.name = "dummy";
        std::string content((std::istreambuf_iterator<char>(myfile)), std::istreambuf_iterator<char>());
        for (int i = 0; i < content.size(); ++i)
        {
            if (content[i] != '\n' || content[i] != '\r' || content[i] != '\t')
                data.description.push_back(content[i]);
        }

        dbData.push_back(data);
        myfile.close();
    }
}

int main()
{
    FillData();
    SaveToDB();
    return 0;
}

