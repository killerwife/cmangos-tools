#include "CreateObjectSearcher.h"
#include <sstream>

std::string update = "UpdateType: CreateObject";
std::string entryObj = "OBJECT_FIELD_ENTRY";
std::string faction = "UNIT_FIELD_FACTIONTEMPLATE";
std::string bounding = "UNIT_FIELD_BOUNDINGRADIUS";
std::string combatreach = "UNIT_FIELD_COMBATREACH";
std::string displayId = "UNIT_FIELD_DISPLAYID";
std::string nativeId = "UNIT_FIELD_NATIVEDISPLAYID";

CreateObjectSearcher::CreateObjectSearcher() : Searcher("CreateObject.txt")
{
}


CreateObjectSearcher::~CreateObjectSearcher()
{
    for (auto& data : m_entries)
    {
        m_outputFile << "UPDATE creature_model_info SET bounding_radius=" + std::to_string(data.second.m_boundingRadius) + ",combat_reach=" + std::to_string(data.second.m_combatReach)
            + " WHERE modelid=" + std::to_string(data.second.m_modelId) +
            "; -- Entry "+ std::to_string(data.second.m_entry) +" Native Model ID: " + std::to_string(data.second.m_nativeModelID) + " Faction ID: " + std::to_string(data.second.m_factionId) << std::endl;
    }
}

bool IsEqual(CreateData& dataA, CreateData& dataB)
{
    if (dataA.m_entry == dataB.m_entry && dataA.m_boundingRadius == dataB.m_boundingRadius && dataA.m_combatReach == dataB.m_combatReach && dataA.m_factionId == dataB.m_factionId &&
        dataA.m_modelId == dataB.m_modelId)
        return true;
    else
        return false;
}

void CreateObjectSearcher::SearchLine(std::string & buffer, Dataclass * dataclass, int start, int finish)
{
    CreateData* data = (CreateData*)dataclass;
    if (FindSubstring(buffer, update, start, finish))
    {
        data->m_isFullPacket = true;
        data->m_entry = 0;
        data->m_factionId = 0;
        data->m_boundingRadius = 0;
        data->m_combatReach = 0;
        data->m_modelId = 0;
        data->m_nativeModelID = 0;
    }
    else if (FindSubstring(buffer, entryObj, start, finish))
    {
        std::string substring = buffer.substr(start + 15, finish  - (start + 15));
        std::string input(100,' ');
        sscanf(substring.data(),"%s%u", input.data(),&data->m_entry);
    }
    else if (FindSubstring(buffer, faction, start, finish))
    {
        std::string substring = buffer.substr(start + 15, finish - (start + 15));
        std::string input(100, ' ');
        sscanf(substring.data(), "%s%u", input.data(), &data->m_factionId);
    }
    else if (FindSubstring(buffer, bounding, start, finish))
    {
        std::string substring = buffer.substr(start + 15, finish - (start + 15));
        std::string input(100, ' ');
        sscanf(substring.data(), "%s%f", input.data(), &data->m_boundingRadius);
    }
    else if (FindSubstring(buffer, combatreach, start, finish))
    {
        std::string substring = buffer.substr(start + 15, finish - (start + 15));
        std::string input(100, ' ');
        sscanf(substring.data(), "%s%f", input.data(), &data->m_combatReach);
    }
    else if (FindSubstring(buffer, displayId, start, finish))
    {
        std::string substring = buffer.substr(start + 15, finish - (start + 15));
        std::string input(100, ' ');
        sscanf(substring.data(), "%s%u", input.data(), &data->m_modelId);
    }
    else if (FindSubstring(buffer, nativeId, start, finish))
    {
        if (!data->m_isFullPacket)
            return;
        if (data->m_modelId == 0)
        {
            data->m_isFullPacket = false;
            return;
        }
        std::string substring = buffer.substr(start + 15, finish - (start + 15));
        std::string input(100, ' ');
        sscanf(substring.data(), "%s%u", input.data(), &data->m_nativeModelID);
        CreateData dataCopy = *data;
        data->m_isFullPacket = false;
        auto itr = m_entries.find(data->m_entry);
        if (itr != m_entries.end())
        {
            if (!IsEqual(dataCopy, (*itr).second))
            {
                std::string output = "Found new data for entry: " + std::to_string(dataCopy.m_entry) + "";
                if (dataCopy.m_boundingRadius != (*itr).second.m_boundingRadius)
                {
                    output += " Different bounding radius Old: " + std::to_string((*itr).second.m_boundingRadius) + " New:" + std::to_string(dataCopy.m_boundingRadius);
                }
                if (dataCopy.m_combatReach != (*itr).second.m_combatReach)
                {
                    output += " Different combat reach Old: " + std::to_string((*itr).second.m_combatReach) + " New:" + std::to_string(dataCopy.m_combatReach);
                }
                if (dataCopy.m_factionId != (*itr).second.m_factionId)
                {
                    output += " Different faction ID Old: " + std::to_string((*itr).second.m_factionId) + " New:" + std::to_string(dataCopy.m_factionId);
                }
                if (dataCopy.m_modelId != (*itr).second.m_modelId)
                {
                    output += " Different model ID Old: " + std::to_string((*itr).second.m_modelId) + " New:" + std::to_string(dataCopy.m_modelId);
                }
                if (dataCopy.m_nativeModelID != (*itr).second.m_nativeModelID)
                {
                    output += " Different native model ID Old: " + std::to_string((*itr).second.m_nativeModelID) + " New:" + std::to_string(dataCopy.m_nativeModelID);
                }
                m_outputFile << output << std::endl;
                m_entries[data->m_entry] = dataCopy;
            }
        }
        else
            m_entries[data->m_entry] = dataCopy;
    }
}
