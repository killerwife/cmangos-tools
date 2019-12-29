#include "SqlBuilder.h"

std::string SqlBuilder::GenerateSqlString(std::string& tableName, std::vector<std::string>& columnNames, std::vector<std::string>& columnData)
{
    std::string firstHalf = "INSERT INTO `" + tableName + "`(";
    std::string secondHalf = ") VALUES(";
    bool first = true;
    for (auto& item : columnNames)
    {
        if (!first)
        {
            firstHalf += ",";
            first = false;
        }
        firstHalf += "`" + item + "`";
    }
    for (auto& item : columnData)
    {
        if (!first)
        {
            secondHalf += ",";
            first = false;
        }
        secondHalf += "`" + item + "`";
    }
    return firstHalf + secondHalf + ");";
}
