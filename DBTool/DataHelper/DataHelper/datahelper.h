#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_datahelper.h"
#include "Composer.h"

class XMLReader;

class DataHelper : public QMainWindow
{
    Q_OBJECT

public:
    DataHelper(XMLReader& reader, QWidget *parent = Q_NULLPTR);

private slots:
    void OpenDbscriptWindow();
    void OpenEAIWindow();
    void OpenMovementWindow();

private:
    Ui::DataHelperClass ui;
    XMLReader& m_reader;
    Composer m_composer;
};
