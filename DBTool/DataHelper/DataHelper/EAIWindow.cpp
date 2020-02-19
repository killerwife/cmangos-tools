#include "EAIWindow.h"
#include "XMLReader.h"
#include "Composer.h"

EAIWindow::EAIWindow(XMLReader& reader, Composer* composer, QWidget *parent)
    : QWidget(parent), Composable(composer)
{
    ui.setupUi(this);
    connect(ui.pushButtonGenerate, SIGNAL(released()), this, SLOT(PushButtonGenerateReleased()));
}

EAIWindow::~EAIWindow()
{
}

void EAIWindow::PushButtonGenerateReleased()
{

}

std::string EAIWindow::GetData()
{
    return std::string();
}
