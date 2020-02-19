#pragma once

#include <QWidget>
#include "ui_EAIWindow.h"
#include "Composable.h"

class XMLReader;
class Composer;

class EAIWindow : public QWidget, public Composable
{
    Q_OBJECT

public:
    EAIWindow(XMLReader& reader, Composer* composer, QWidget *parent = Q_NULLPTR);
    ~EAIWindow();

    virtual std::string GetData() override;

private slots:
    void PushButtonGenerateReleased();

private:
    Ui::EAIWindow ui;
};
