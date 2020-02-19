#pragma once

#include <string>

class Composer;

class Composable
{
    public:
        Composable(Composer* composer) : m_composer(composer) {}

        virtual std::string GetData() = 0;

        Composer& GetComposer() { return *m_composer; }

    private:
        Composer* m_composer;
};