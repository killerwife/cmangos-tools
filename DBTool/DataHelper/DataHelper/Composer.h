#pragma once
#include <QTextEdit>

class Composable;

class Composer
{
    public:
        Composer(QTextEdit* outputWindow = nullptr);

        void AddComposable(Composable* composable);
        void RemoveComposable(Composable* composable);
        void Update();

        void SetOutputWindow(QTextEdit* outputWindow) { m_outputWindow = outputWindow; }

    private:
        QTextEdit* m_outputWindow;
        std::vector<Composable*> m_composables;
};