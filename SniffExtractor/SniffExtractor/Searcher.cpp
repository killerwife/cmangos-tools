#include "Searcher.h"

Searcher::Searcher() : m_outputFile("output.txt")
{
}

Searcher::Searcher(std::string filename) : m_outputFile(filename)
{
}


Searcher::~Searcher()
{
}

void Searcher::RunSearch(std::string &buffer)
{
    size_t i = 0;
    Dataclass* dataclass = GetDataclass();
    while (i < buffer.size())
    {
        size_t k = i, l = 0;
        while (i < buffer.size())
        {
            if (buffer[i] == '\n')
            {
                l = i++;
                break;
            }

            i++;
        }

        SearchLine(buffer, dataclass, k, l);
    }
}

bool Searcher::FindSubstring(std::string const& text, std::string const& substring, int start, const int finish)
{
    for (; start < finish; start++)
    {
        if (text[start] == substring[0])
        {
            int k = 0;
            for (int i = start; i < text.size(), k < substring.size(); i++, k++)
            {
                if (text[i] != substring[k])
                    break;
            }
            if (k == substring.size())
                return true;
        }
    }
    return false;
}
