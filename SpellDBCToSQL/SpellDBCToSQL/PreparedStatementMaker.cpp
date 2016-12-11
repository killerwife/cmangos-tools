#include "PreparedStatementMaker.h"
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <iostream>


PreparedStatementMaker::PreparedStatementMaker()
{
}


PreparedStatementMaker::~PreparedStatementMaker()
{
}

void PreparedStatementMaker::MakePreparedStatement(std::string filename, std::string & output)
{
    std::string path = "tableSchemas/" + filename + ".txt";
    std::ifstream input(path);
    std::string tableNames = "";
    std::string specifiers = "";
    std::string line;
    std::getline(input, line);
    std::getline(input, line);
    std::getline(input, line);
    std::getline(input, line); // skip create table lines
    std::string bigintText = " bigint";
    std::string intText = " int";
    std::string unsignedText = " unsigned";
    std::string floatText = " float";
    std::string textText = " text";
    bool first = true;
    while (!input.eof())
    {
        std::getline(input,line);
        if (line[0] == ')' || line.find("PRIMARY") != std::string::npos)
            break;

        std::string tableName;
        bool startReading = false;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '`')
            {
                if(!startReading)
                    startReading = true;
                else
                {
                    tableName += line[i];
                    break;
                }
            }
            if (startReading)
                tableName += line[i];
        }
        std::string specifier;
        
        if (line.find(bigintText) != std::string::npos)
            specifier += "'%llu'";
        else if (line.find(unsignedText) != std::string::npos)
            specifier += "'%u'";
        else if(line.find(intText) != std::string::npos)
            specifier += "'%i'";
        else if (line.find(floatText) != std::string::npos)
            specifier += "'%f'";
        else if (line.find(textText) != std::string::npos)
            specifier += "'%s'";

        if (!first)
        {
            tableNames+= ",  " + tableName;
            specifiers+= ", " + specifier;
        }
        else
        {
            first = false;
            tableNames += tableName;
            specifiers += specifier;
        }
    }
    output = "INSERT INTO %s (" + tableNames + ") VALUES (" + specifiers + ")";
    //printf("%s",output.data());
}
