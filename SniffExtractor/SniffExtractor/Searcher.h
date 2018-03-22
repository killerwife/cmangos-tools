#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <mutex>

struct Dataclass
{

};

class Searcher
{
public:
    Searcher();
    Searcher(std::string filename);
    ~Searcher();

    void RunSearch(std::string &buffer);
    bool FindSubstring(std::string const& text, std::string const& substring, int start, const int finish);

    virtual void SearchLine(std::string& buffer, Dataclass* dataclass, int start, int finish) {}
    virtual Dataclass* GetDataclass() { return new Dataclass(); }

protected:
    std::mutex m_lockerOutput;
    std::ofstream m_outputFile;
};

