#pragma once
#include "Searcher.h"

struct Position : Dataclass
{
    std::string m_positionLine;
    bool nonStationary;
};

class PositionSearcher :
    public Searcher
{
public:
    PositionSearcher();
    ~PositionSearcher();

    virtual void SearchLine(std::string& buffer, Dataclass* dataclass, int start, int finish) override;

    Dataclass* GetDataclass() override { return new Position(); }
};

