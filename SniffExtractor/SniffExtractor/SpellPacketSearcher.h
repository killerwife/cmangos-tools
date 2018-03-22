#pragma once
#include "Searcher.h"
#include <map>
#include <set>

struct SpellCreaturePair : Dataclass
{
    bool m_started;
    uint32_t m_entry;
    uint32_t m_spellId;
};

class SpellPacketSearcher :
    public Searcher
{
public:
    SpellPacketSearcher();
    ~SpellPacketSearcher();

    virtual void SearchLine(std::string& buffer, Dataclass* dataclass, int start, int finish) override;

    Dataclass* GetDataclass() override { return new SpellCreaturePair(); }

    std::map<uint32_t, std::set<uint32_t>> m_spellCasterPair;
};

