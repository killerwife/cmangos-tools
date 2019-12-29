#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_datahelper.h"

class XMLReader;

class DataHelper : public QMainWindow
{
    Q_OBJECT

public:
    DataHelper(XMLReader& reader, QWidget *parent = Q_NULLPTR);

private slots:
    void ComboBoxDbscriptChanged(int index);
    void PushButtonDbscriptReleased();

private:
    Ui::DataHelperClass ui;
    XMLReader& m_reader;
    std::vector<std::map<std::string, std::string>> m_dbscriptData;
};
