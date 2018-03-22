#include "SpellPacketSearcher.h"

std::string startPacket = "SMSG_SPELL_START";
std::string goPacket = "SMSG_SPELL_GO";
std::string guidLine = "Caster  Unit/Player/Item  GUID: Full: 0xF001";
std::string spellLine = "Spell ID:";

SpellPacketSearcher::SpellPacketSearcher() : Searcher("SpellCaster.txt")
{
}


SpellPacketSearcher::~SpellPacketSearcher()
{
    for (auto& dataVector : m_spellCasterPair)
    {
        m_outputFile << "Creature ID: " << std::to_string(dataVector.first) << " Spell IDs: ";
        for (auto& data : dataVector.second)
        {
            m_outputFile << std::to_string(data) << " ";
        }
        m_outputFile << std::endl;
    }
}

void SpellPacketSearcher::SearchLine(std::string & buffer, Dataclass * dataclass, int start, int finish)
{
    SpellCreaturePair* data = (SpellCreaturePair*)dataclass;
    if (FindSubstring(buffer, startPacket, start, finish) || FindSubstring(buffer, goPacket, start, finish))
    {
        data->m_started = true;
        data->m_entry = 0;
        data->m_spellId = 0;
    }
    else if (FindSubstring(buffer, guidLine, start, finish))
    {
        std::string substring = buffer.substr(start + 44, 4);
        std::string input(100, ' ');
        uint32_t entry = 0;
        sscanf(substring.data(), "%x", &entry);
        if (data->m_started && entry)
        {
            data->m_entry = entry;
            data->m_started = false;
        }
    }
    else if (FindSubstring(buffer, spellLine, start, finish))
    {
        std::string substring = buffer.substr(start + 10, finish - (start + 10));
        std::string input(100, ' ');
        sscanf(substring.data(), "%u", &data->m_spellId);
        if (data->m_entry)
        {
            std::lock_guard<std::mutex> guard(m_lockerOutput);
            m_spellCasterPair[data->m_entry].insert(data->m_spellId);
        }
        data->m_entry = 0;
        data->m_started = false;
    }
}
