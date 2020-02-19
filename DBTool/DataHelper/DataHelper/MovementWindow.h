#pragma once

#include <QWidget>
#include "ui_MovementWindow.h"

class MovementWindow : public QWidget
{
    Q_OBJECT

public:
    MovementWindow(QWidget *parent = Q_NULLPTR);
    ~MovementWindow();

private:
    Ui::MovementWindow ui;
};
