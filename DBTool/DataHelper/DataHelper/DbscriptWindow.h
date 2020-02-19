#pragma once

#include <QWidget>
#include "ui_DbscriptWindow.h"
#include "Composable.h"

#include "Defines.h"

class XMLReader;
class Composer;

struct Dbscript
{
    uint32 id;
    uint32 delay;
    uint32 priority;
    uint32 command;
    uint32 datalong[3];
    uint32 buddyEntry;
    uint32 searchRadius;
    uint32 dataFlags;
    int32 dataInt[4];
    Position position;
    std::string comment;

    std::string GetData();
};

class DbscriptWindow : public QWidget, public Composable
{
    Q_OBJECT

public:
    DbscriptWindow(XMLReader& reader, Composer* composer, QWidget *parent = Q_NULLPTR);
    ~DbscriptWindow();

    virtual std::string GetData() override;

private slots:
    void ComboBoxDbscriptChanged(int index);
    void PushButtonGenerateReleased();

private:
    Ui::DbscriptWindow ui;
    std::vector<std::map<std::string, std::string>> m_dbscriptData;
    std::vector<Dbscript> m_generatedData;
};
