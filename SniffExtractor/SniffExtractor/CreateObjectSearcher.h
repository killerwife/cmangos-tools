#pragma once
#include "Searcher.h"
#include <map>

struct CreateData : Dataclass
{
    bool m_isFullPacket;
    uint32_t m_entry;
    uint32_t m_modelId;
    uint32_t m_nativeModelID;
    uint32_t m_factionId;
    float m_boundingRadius;
    float m_combatReach;
};

class CreateObjectSearcher :
    public Searcher
{
public:
    CreateObjectSearcher();
    ~CreateObjectSearcher();

    virtual void SearchLine(std::string& buffer, Dataclass* dataclass, int start, int finish) override;

    Dataclass* GetDataclass() override { return new CreateData(); }
    std::map<int, CreateData> m_entries;
};

