#include "Composer.h"
#include "Composable.h"

Composer::Composer(QTextEdit* outputWindow) : m_outputWindow(outputWindow)
{
}

void Composer::AddComposable(Composable* composable)
{
    m_composables.push_back(composable);
}

void Composer::RemoveComposable(Composable* composable)
{
    // TODO:
}

void Composer::Update()
{
    std::string output = "";
    for (auto composable : m_composables)
        output += composable->GetData();
    m_outputWindow->setText(output.data());
}
