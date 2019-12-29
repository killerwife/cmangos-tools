#include "datahelper.h"
#include "XMLReader.h"

DataHelper::DataHelper(XMLReader& reader, QWidget* parent)
    : QMainWindow(parent), m_reader(reader)
{
    ui.setupUi(this);
    connect(ui.comboBoxDbscript, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxDbscriptChanged(int)));
    connect(ui.pushButtonGenerateSQLDbscript, SIGNAL(released()), this, SLOT(PushButtonDbscriptReleased()));
    m_dbscriptData = reader.GetDbscriptData();
    for (int i = 0; i < m_dbscriptData.size(); ++i)
        ui.comboBoxDbscript->addItem((std::to_string(i + 1) + ". " + m_dbscriptData[i]["Name"] + " " + m_dbscriptData[i]["Description"]).data());
}

void DataHelper::ComboBoxDbscriptChanged(int index)
{
    if (index < m_dbscriptData.size())
    {
        ui.labelDataLong1->setText(m_dbscriptData[index]["DataLong1"].data());
    }
}

void DataHelper::PushButtonDbscriptReleased()
{
    printf("");
}
