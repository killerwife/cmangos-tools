#pragma once
#include <string>
#include <vector>

class SqlBuilder
{
    public:
        SqlBuilder();

        std::string GenerateSqlString(std::string& tableName, std::vector<std::string>& columnNames, std::vector<std::string>& columnData);

    private:

};

