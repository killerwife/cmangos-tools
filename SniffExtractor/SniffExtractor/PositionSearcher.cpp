#include "PositionSearcher.h"

std::string strings[] =
{
    "OBJECT_FIELD_ENTRY: 180398",
    "OBJECT_FIELD_ENTRY: 180396",
    "OBJECT_FIELD_ENTRY: 180397",
    "OBJECT_FIELD_ENTRY: 180400",
    "OBJECT_FIELD_ENTRY: 180399",
    "OBJECT_FIELD_ENTRY: 180394",
    "OBJECT_FIELD_ENTRY: 185107",
    "OBJECT_FIELD_ENTRY: 180395",
    "OBJECT_FIELD_ENTRY: 185106",
    "OBJECT_FIELD_ENTRY: 12220",
};

std::string stationaryPosition("Stationary Position: X:");
std::string position("Position: X:");
std::string orientation("Orientation:");

#define kCommandsCount  ( sizeof(strings) / sizeof(strings[ 0 ]) )

PositionSearcher::PositionSearcher() : Searcher("positions.txt")
{
}


PositionSearcher::~PositionSearcher()
{
}

void PositionSearcher::SearchLine(std::string & buffer, Dataclass* dataclass, int start, int finish)
{
    std::string line;

    Position* positionData = (Position*) dataclass;

    if (FindSubstring(buffer, stationaryPosition, start, finish))
        positionData->m_positionLine = buffer.substr(start, finish - start);
    else if (FindSubstring(buffer, position, start, finish))
    {
        positionData->m_positionLine = buffer.substr(start, finish - start);
        positionData->nonStationary = true;
    }
    else if (positionData->nonStationary && FindSubstring(buffer, orientation, start, finish))
    {
        positionData->m_positionLine += " " + buffer.substr(start + 4, finish - start - 4);
        positionData->nonStationary = false;
    }
    else
    {
        for (int i = 0; i < kCommandsCount; i++)
        {
            if (FindSubstring(buffer, strings[i], start, finish))
            {
                std::lock_guard<std::mutex> guard(m_lockerOutput);
                std::string substring = buffer.substr(start, finish - start);
                m_outputFile << substring << std::endl;
                m_outputFile << positionData->m_positionLine << std::endl;
                break;
            }
        }
    }
}
