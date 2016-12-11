#include <string>
class DBCExport
{
public:
    DBCExport();
    ~DBCExport();
    void ExportDBCToSQLTBC(std::string tableName);
    void ExportDBCToSQLWotlk(std::string tableName);
    void ExportDBCToSQLClassic(std::string tableName);
};

