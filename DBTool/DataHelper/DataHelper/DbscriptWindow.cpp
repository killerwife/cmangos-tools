#include "DbscriptWindow.h"
#include "XMLReader.h"
#include "Composer.h"

std::string tableNames[]
{
    "dbscripts_on_creature_death",
    "dbscripts_on_creature_movement",
    "dbscripts_on_event",
    "dbscripts_on_go_template_use",
    "dbscripts_on_go_use",
    "dbscripts_on_gossip",
    "dbscripts_on_quest_end",
    "dbscripts_on_quest_start",
    "dbscripts_on_spell",
    "dbscripts_on_relay",
};

DbscriptWindow::DbscriptWindow(XMLReader& reader, Composer* composer, QWidget *parent)
    : QWidget(parent), Composable(composer)
{
    ui.setupUi(this);
    connect(ui.comboBoxDbscript, SIGNAL(currentIndexChanged(int)), this, SLOT(ComboBoxDbscriptChanged(int)));
    connect(ui.pushButtonGenerateSQL, SIGNAL(released()), this, SLOT(PushButtonGenerateReleased()));
    m_dbscriptData = reader.GetDbscriptData();
    for (int i = 0; i < m_dbscriptData.size(); ++i)
        ui.comboBoxDbscript->addItem((std::to_string(i + 1) + ". " + m_dbscriptData[i]["Name"] + " " + m_dbscriptData[i]["Description"]).data());
    for (int i = 0; i < sizeof(tableNames) / sizeof(*tableNames); ++i)
        ui.comboBoxTable->addItem(tableNames[i].data());

    ui.tableWidget->setRowCount(0);
    ui.tableWidget->setColumnCount(19);
    ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    ui.tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
    ui.tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Delay"));
    ui.tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Priority"));
    ui.tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Command"));

    ui.tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("DataLong1"));
    ui.tableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem("DataLong2"));
    ui.tableWidget->setHorizontalHeaderItem(6, new QTableWidgetItem("DataLong3"));

    ui.tableWidget->setHorizontalHeaderItem(7, new QTableWidgetItem("BuddyEntry"));
    ui.tableWidget->setHorizontalHeaderItem(8, new QTableWidgetItem("SearchRadius"));
    ui.tableWidget->setHorizontalHeaderItem(9, new QTableWidgetItem("Flags"));

    ui.tableWidget->setHorizontalHeaderItem(10, new QTableWidgetItem("DataInt1"));
    ui.tableWidget->setHorizontalHeaderItem(11, new QTableWidgetItem("DataInt2"));
    ui.tableWidget->setHorizontalHeaderItem(12, new QTableWidgetItem("DataInt3"));
    ui.tableWidget->setHorizontalHeaderItem(13, new QTableWidgetItem("DataInt4"));

    ui.tableWidget->setHorizontalHeaderItem(14, new QTableWidgetItem("X"));
    ui.tableWidget->setHorizontalHeaderItem(15, new QTableWidgetItem("Y"));
    ui.tableWidget->setHorizontalHeaderItem(16, new QTableWidgetItem("Z"));
    ui.tableWidget->setHorizontalHeaderItem(17, new QTableWidgetItem("Ori"));

    ui.tableWidget->setHorizontalHeaderItem(18, new QTableWidgetItem("Comment"));

    GetComposer().AddComposable(this);
}

DbscriptWindow::~DbscriptWindow()
{
    GetComposer().RemoveComposable(this);
}

std::string DbscriptWindow::GetData()
{
    if (ui.comboBoxTable->currentIndex() > sizeof(tableNames) || m_generatedData.empty())
        return "";
    std::string output = "INSERT INTO " + tableNames[ui.comboBoxTable->currentIndex()] + " VALUES(id, delay, priority, command, datalong, datalong2, datalong3, buddy_entry, search_radius, data_flags, dataint, dataint2, dataint3, dataint4, x, y, z, o, comments)\n";
    for (auto& data : m_generatedData)
        output += data.GetData() + "\n";
    return output;
}

void DbscriptWindow::ComboBoxDbscriptChanged(int index)
{
    if (index < m_dbscriptData.size())
    {
        ui.labelDataLong1->setText(m_dbscriptData[index]["DataLong1"].data());
        ui.labelDataLong2->setText(m_dbscriptData[index]["DataLong2"].data());
        ui.labelDataLong3->setText(m_dbscriptData[index]["DataLong3"].data());

        ui.labelDataInt1->setText(m_dbscriptData[index]["DataInt1"].data());
        ui.labelDataInt2->setText(m_dbscriptData[index]["DataInt2"].data());
        ui.labelDataInt3->setText(m_dbscriptData[index]["DataInt3"].data());
        ui.labelDataInt4->setText(m_dbscriptData[index]["DataInt4"].data());

        ui.labelX->setText(m_dbscriptData[index]["X"].data());
        ui.labelY->setText(m_dbscriptData[index]["Y"].data());
        ui.labelZ->setText(m_dbscriptData[index]["Z"].data());
        ui.labelOri->setText(m_dbscriptData[index]["Ori"].data());

        ui.labelBuddyEntry->setText(m_dbscriptData[index]["BuddyEntry"].data());
        ui.labelSearchRadius->setText(m_dbscriptData[index]["SearchRadius"].data());
        ui.checkBoxFlagAdditionalCommand->setText(m_dbscriptData[index]["AdditionalCommand"].data());
    }
}

void DbscriptWindow::PushButtonGenerateReleased()
{
    Dbscript data;
    data.id = ui.lineEditDBScriptID->text().toInt();
    data.delay = ui.lineEditDelay->text().toInt();
    data.priority = ui.lineEditPriority->text().toInt();
    data.command = ui.comboBoxDbscript->currentIndex();

    data.datalong[0] = ui.lineEditDataLong1->text().toInt();
    data.datalong[1] = ui.lineEditDataLong2->text().toInt();
    data.datalong[2] = ui.lineEditDataLong3->text().toInt();

    data.buddyEntry = ui.lineEditBuddyEntry->text().toInt();
    data.searchRadius = ui.lineEditSearchRadius->text().toInt();

    data.dataInt[0] = ui.lineEditDataInt1->text().toInt();
    data.dataInt[1] = ui.lineEditDataInt2->text().toInt();
    data.dataInt[2] = ui.lineEditDataInt3->text().toInt();
    data.dataInt[3] = ui.lineEditDataInt4->text().toInt();

    data.position.x = ui.lineEditX->text().toFloat();
    data.position.y = ui.lineEditY->text().toFloat();
    data.position.z = ui.lineEditZ->text().toFloat();
    data.position.ori = ui.lineEditOri->text().toFloat();

    data.comment = ui.lineEditDBScriptComment->text().toStdString();

    uint32 flags = 0;
    if (ui.checkBoxFlag1->isChecked())
        flags |= 1;
    if (ui.checkBoxFlag2->isChecked())
        flags |= 2;
    if (ui.checkBoxFlag3->isChecked())
        flags |= 4;
    if (ui.checkBoxFlagAdditionalCommand->isChecked())
        flags |= 8;
    if (ui.checkBoxFlag5->isChecked())
        flags |= 16;
    if (ui.checkBoxFlag6->isChecked())
        flags |= 32;
    if (ui.checkBoxFlag7->isChecked())
        flags |= 64;
    if (ui.checkBoxFlag8->isChecked())
        flags |= 128;
    data.dataFlags = flags;
    int index = ui.tableWidget->rowCount();
    ui.tableWidget->setRowCount(index + 1);
    ui.tableWidget->setItem(index, 0, new QTableWidgetItem(QString::number(data.id)));
    ui.tableWidget->setItem(index, 1, new QTableWidgetItem(QString::number(data.delay)));
    ui.tableWidget->setItem(index, 2, new QTableWidgetItem(QString::number(data.priority)));
    ui.tableWidget->setItem(index, 3, new QTableWidgetItem(QString::number(data.command)));

    ui.tableWidget->setItem(index, 4, new QTableWidgetItem(QString::number(data.datalong[0])));
    ui.tableWidget->setItem(index, 5, new QTableWidgetItem(QString::number(data.datalong[1])));
    ui.tableWidget->setItem(index, 6, new QTableWidgetItem(QString::number(data.datalong[2])));

    ui.tableWidget->setItem(index, 7, new QTableWidgetItem(QString::number(data.buddyEntry)));
    ui.tableWidget->setItem(index, 8, new QTableWidgetItem(QString::number(data.searchRadius)));
    ui.tableWidget->setItem(index, 9, new QTableWidgetItem(QString::number(data.dataFlags)));

    ui.tableWidget->setItem(index, 10, new QTableWidgetItem(QString::number(data.dataInt[0])));
    ui.tableWidget->setItem(index, 11, new QTableWidgetItem(QString::number(data.dataInt[1])));
    ui.tableWidget->setItem(index, 12, new QTableWidgetItem(QString::number(data.dataInt[2])));
    ui.tableWidget->setItem(index, 13, new QTableWidgetItem(QString::number(data.dataInt[3])));

    ui.tableWidget->setItem(index, 14, new QTableWidgetItem(QString::number(data.position.x)));
    ui.tableWidget->setItem(index, 15, new QTableWidgetItem(QString::number(data.position.y)));
    ui.tableWidget->setItem(index, 16, new QTableWidgetItem(QString::number(data.position.z)));
    ui.tableWidget->setItem(index, 17, new QTableWidgetItem(QString::number(data.position.ori)));

    ui.tableWidget->setItem(index, 18, new QTableWidgetItem(data.comment.data()));
    m_generatedData.push_back(data);
    GetComposer().Update();
}

std::string Dbscript::GetData()
{
    return "(" + std::to_string(id) + "," + std::to_string(delay) + "," + std::to_string(priority) + "," + std::to_string(command) + "," + std::to_string(datalong[0]) + "," + std::to_string(datalong[1]) + "," +
        std::to_string(datalong[2]) + "," + std::to_string(buddyEntry) + "," + std::to_string(searchRadius) + "," + std::to_string(dataFlags) + "," + std::to_string(dataInt[0]) + "," + std::to_string(dataInt[1]) + "," + std::to_string(dataInt[2]) + "," +
        std::to_string(dataInt[3]) + "," + std::to_string(position.x) + "," + std::to_string(position.y) + "," + std::to_string(position.z) + "," + std::to_string(position.ori) + ",'" + comment + "'," + ")\n";
}
