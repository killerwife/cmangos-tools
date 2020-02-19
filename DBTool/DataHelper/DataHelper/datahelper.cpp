#include "datahelper.h"
#include "XMLReader.h"
#include "DbscriptWindow.h"

DataHelper::DataHelper(XMLReader& reader, QWidget* parent)
    : QMainWindow(parent), m_reader(reader)
{
    ui.setupUi(this);
    m_composer.SetOutputWindow(ui.textEditOutput);
    connect(ui.pushButtonDbscript, SIGNAL(released()), this, SLOT(OpenDbscriptWindow()));
}

void DataHelper::OpenDbscriptWindow()
{
    DbscriptWindow* window = new DbscriptWindow(m_reader, &m_composer);
    window->show();
}

void DataHelper::OpenEAIWindow()
{

}

void DataHelper::OpenMovementWindow()
{

}
