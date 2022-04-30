#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "chartwindow.h"
#include "chartselection.h"
#include "chartsettings.h"
#include "flags.h"

#include <QObject>
#include <QVector>
#include <QWidget>

class Controller : public QWidget{
    Q_OBJECT
private:
    MainWindow* _MainWindow;
    QVector<ChartWindow*> _ChartWindows;
    ChartSelection* _ChartSelection;
    ChartSettings* _ChartSettings;
    QMap<QString, QString> _ActiveFiles;

    QTableWidget* fileParser(const QString);
    bool TableParser(const QString&);
    void lastSessionRestore();
    void fileSave(int);
    //Unire fileSave con fileOverwrite
    void fileOverwrite(QString, int);
    void fileOpen(QString = "");
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
    void SpinBox();
    void setTextSize();
    void tabClose(int);

    /* File Managment */
    void openFile();
    void newTab();
    void overwrite();

    void mainWindowCloseEvent();
};

#endif // CONTROLLER_H
