#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "chartwindow.h"
#include "chartselection.h"
#include "chartsettings.h"

#include <QObject>
#include <QVector>
#include <QWidget>

class Controller : public QWidget
{
    Q_OBJECT
private:
    MainWindow* _MainWindow;
    QVector<ChartWindow*> _ChartWindows;
    ChartSelection* _ChartSelection;
    ChartSettings* _ChartSettings;
public:
    Controller();
public slots:
    void NewChart(); //TBD : void o bool? Parametri?
    void ChangeChart(); //TBD : void o bool? Parametri?

    /* MainWindow slots */
    void UpperInsert();
    void LowerInsert();
    void LeftInsert();
    void RightInsert();
    void TableReset();
    void RowReset();
    void ColumnReset();
    void RowDelete();
    void ColumnDelete();
    void LeftAlign();
    void CenterAlign();
    void RightAlign();
    void SpinBoxRefresh();
};

#endif // CONTROLLER_H
