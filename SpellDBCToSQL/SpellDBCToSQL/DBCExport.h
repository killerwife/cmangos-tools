#include <string>
#include <memory>
#include <functional>
#include <cppconn/statement.h>
#include "SharedDefines.h"
class DBCExport
{
public:
    DBCExport();
    ~DBCExport();
    static void ExportDBCToSQLTBC(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    static void ExportDBCToSQLWotlk(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    static void ExportDBCToSQLClassic(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    static void ExportDungeonEncounters(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    static void ExportFactionsTBC(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    static void ExportFactionsWOTLK(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
    void ExportDBCGeneric(std::string tableName, std::function<void(std::string&, std::string&, std::unique_ptr<sql::Statement>&)> executor);
    static void ExportAreaGroupWotlk(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
};

