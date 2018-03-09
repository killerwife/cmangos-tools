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
    void ExportDBCToSQLTBC(std::string tableName);
    void ExportDBCToSQLWotlk(std::string tableName);
    void ExportDBCToSQLClassic(std::string tableName);
    void ExportDungeonEncounters(std::string tableName);
    void ExportFactionsTBC(std::string tableName);
    void ExportFactionsWOTLK(std::string tableName);
    void ExportDBCGeneric(std::string tableName, std::function<void(std::string&, std::string&, std::unique_ptr<sql::Statement>&)> executor);
    static void ExportAreaGroupWotlk(std::string& tableName, std::string& statement, std::unique_ptr<sql::Statement>& stmt);
};

