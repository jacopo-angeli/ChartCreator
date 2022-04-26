#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"

#include <QObject>
#include <QWidget>

class Controller
{
    Q_OBJECT
private:
    MainWindow* _MainWindow;

public:
    Controller();
};

#endif // CONTROLLER_H
