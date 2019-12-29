#include "XMLReader.h"
#include <exception>

XMLReader::XMLReader(std::string fileName) : m_fileName(fileName), m_file(fileName.data())
{
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        throw std::exception("Xml loading failed");
        return;
    }
    m_xmlReader.setDevice(&m_file);
}

std::vector<std::map<std::string, std::string>> XMLReader::GetDbscriptData()
{
    std::vector<std::map<std::string, std::string>> output;
    int i = 0;
    while (!m_xmlReader.atEnd() && !m_xmlReader.hasError())
    {
        // Read next element
        QXmlStreamReader::TokenType token = m_xmlReader.readNext();
        //If token is just StartDocument - go to next
        if (token == QXmlStreamReader::StartDocument)
        {
            continue;
        }
        //If token is StartElement - read it
        if (token == QXmlStreamReader::StartElement)
        {
            if (m_xmlReader.name() == "Data")
            {
                continue;
            }
            if (m_xmlReader.name() == "DBScript")
            {
                m_xmlReader.readNext();
                m_xmlReader.readNext();
                while (m_xmlReader.name() == "Command")
                {
                    std::map<std::string, std::string> container;
                    for (auto& data : m_xmlReader.attributes())
                        container.emplace(std::string(data.name().toUtf8()), std::string(data.value().toUtf8()));
                    output.push_back(container);
                    m_xmlReader.readNext();
                    m_xmlReader.readNext();
                    std::string name = m_xmlReader.name().toUtf8();
                    ++i;
                }
            }
        }
    }
    return output;
}
