#include "CreatureTemplateSearcher.h"
#include <sstream>

std::string packet = "SMSG_CREATURE_QUERY_RESPONSE";
std::string entry = "Entry:";
std::string name = "[0] Name:";
std::string model1 = "[0] Display ID:";
std::string model2 = "[1] Display ID:";
std::string model3 = "[2] Display ID:";
std::string model4 = "[3] Display ID:";
std::string healthMult = "HealthMultriplier:";
std::string manaMult = "ManaMultiplier:";

CreatureTemplateSearcher::CreatureTemplateSearcher() : Searcher("template.txt")
{
}


CreatureTemplateSearcher::~CreatureTemplateSearcher()
{
    for (auto& data : m_entries)
    {
        m_outputFile << "UPDATE creature_template SET ModelId1=" + std::to_string(data.second.m_modelIds[0]) + ",ModelId2=" + std::to_string(data.second.m_modelIds[1]) +
            ",ModelId3=" + std::to_string(data.second.m_modelIds[2]) + ",ModelId4=" + std::to_string(data.second.m_modelIds[3]) + " WHERE entry=" + std::to_string(data.second.m_entry) +
            "; -- name: " + data.second.m_name + " Health Multiplier: " + std::to_string(data.second.m_healthMultiplier) + " Mana Multiplier: " + std::to_string(data.second.m_manaMultiplier) << std::endl;
    }
}

bool IsEqual(TemplateData& dataA, TemplateData& dataB)
{
    if (dataA.m_entry == dataB.m_entry && dataA.m_healthMultiplier == dataB.m_healthMultiplier && dataA.m_manaMultiplier == dataB.m_manaMultiplier &&
        dataA.m_modelIds[0] == dataB.m_modelIds[0] && dataA.m_modelIds[1] == dataB.m_modelIds[1] && dataA.m_modelIds[2] == dataB.m_modelIds[2] && dataA.m_modelIds[3] == dataB.m_modelIds[3])
        return true;
    else
        return false;
}

void CreatureTemplateSearcher::SearchLine(std::string &buffer, Dataclass* dataclass, int start, int finish)
{
    TemplateData* data = (TemplateData*)dataclass;
    if (FindSubstring(buffer, packet, start, finish))
    {
        data->m_entry = 0;
        for (int i = 0; i < 4; i++) data->m_modelIds[i] = 0;
        data->m_name = "";
        data->m_healthMultiplier = 0;
        data->m_manaMultiplier = 0;
    }
    else
    {
        if (FindSubstring(buffer, entry, start, finish))
        {
            std::string substring = buffer.substr(start + 6, finish - (start + 6));
            std::stringstream ss(substring);
            ss >> data->m_entry;
        }
        else
        {
            if (FindSubstring(buffer, name, start, finish))
            {
                data->m_name = buffer.substr(start + 9, finish - (start + 9));
            }
            else
            {
                if (FindSubstring(buffer, model1, start, finish))
                {
                    std::string substring = buffer.substr(start + 15, finish - (start + 15));
                    std::stringstream ss(substring);
                    ss >> data->m_modelIds[0];
                }
                else
                {
                    if (FindSubstring(buffer, model2, start, finish))
                    {
                        std::string substring = buffer.substr(start + 15, finish - (start + 15));
                        std::stringstream ss(substring);
                        ss >> data->m_modelIds[1];
                    }
                    else
                    {
                        if (FindSubstring(buffer, model3, start, finish))
                        {
                            std::string substring = buffer.substr(start + 15, finish - (start + 15));
                            std::stringstream ss(substring);
                            ss >> data->m_modelIds[2];
                        }
                        else
                        {
                            if (FindSubstring(buffer, model4, start, finish))
                            {
                                std::string substring = buffer.substr(start + 15, finish - (start + 15));
                                std::stringstream ss(substring);
                                ss >> data->m_modelIds[3];
                            }
                            else
                            {
                                if (FindSubstring(buffer, healthMult, start, finish))
                                {
                                    std::string substring = buffer.substr(start + 19, finish - (start + 19));
                                    std::stringstream ss(substring);
                                    ss >> data->m_healthMultiplier;
                                }
                                else
                                {
                                    if (FindSubstring(buffer, manaMult, start, finish))
                                    {
                                        std::string substring = buffer.substr(start + 15, finish - (start + 15));
                                        std::stringstream ss(substring);
                                        ss >> data->m_manaMultiplier;
                                        std::lock_guard<std::mutex> guard(m_lockerOutput);
                                        TemplateData dataCopy;
                                        dataCopy.m_entry = data->m_entry;
                                        dataCopy.m_healthMultiplier = data->m_healthMultiplier;
                                        dataCopy.m_manaMultiplier = data->m_manaMultiplier;
                                        dataCopy.m_name = data->m_name;
                                        dataCopy.m_modelIds[0] = data->m_modelIds[0];
                                        dataCopy.m_modelIds[1] = data->m_modelIds[1];
                                        dataCopy.m_modelIds[2] = data->m_modelIds[2];
                                        dataCopy.m_modelIds[3] = data->m_modelIds[3];
                                        auto itr = m_entries.find(data->m_entry);
                                        if (itr != m_entries.end())
                                        {
                                            if (!IsEqual(dataCopy, (*itr).second))
                                            {
                                                m_outputFile << "Found newer data for " + (*itr).second.m_name + " Entry: " + std::to_string(dataCopy.m_entry) + " Old Data: " + std::to_string((*itr).second.m_modelIds[0]) + " "
                                                    + std::to_string((*itr).second.m_modelIds[1]) + " " + std::to_string((*itr).second.m_modelIds[2]) + " " + std::to_string((*itr).second.m_modelIds[3]) + " "
                                                    + std::to_string((*itr).second.m_healthMultiplier) + " " + std::to_string((*itr).second.m_manaMultiplier) << std::endl;
                                                m_entries[data->m_entry] = dataCopy;
                                            }
                                        }
                                        else
                                            m_entries[data->m_entry] = dataCopy;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
