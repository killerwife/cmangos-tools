#pragma once
#include <string>
#include <map>
#include <vector>
#include <QFile>
#include <QXmlStreamReader>

class XMLReader
{
    public:
        XMLReader(std::string fileName);

        std::vector<std::map<std::string, std::string>> GetDbscriptData();
    private:
        std::string m_fileName;
        QFile m_file;
        QXmlStreamReader m_xmlReader;
};

