#pragma once
#include "Searcher.h"
#include <map>

struct TemplateData : Dataclass
{
    uint32_t m_entry;
    uint32_t m_modelIds[4];
    std::string m_name;
    float m_healthMultiplier;
    float m_manaMultiplier;
};

class CreatureTemplateSearcher :
    public Searcher
{
public:
    CreatureTemplateSearcher();
    ~CreatureTemplateSearcher();

    virtual void SearchLine(std::string& buffer, Dataclass* dataclass, int start, int finish) override;

    Dataclass* GetDataclass() override { return new TemplateData(); }
    std::map<int,TemplateData> m_entries;
};

