#include <string>
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
};

