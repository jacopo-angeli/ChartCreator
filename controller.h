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
    QMap<QString, QString> _ActiveFiles;

    QTableWidget* fileParser(const QString);
    void lastSessionRestore();
    void fileSave(int, QString = "");
    void fileOpen(QString = "");
    QString positionTag(QModelIndexList*);
    bool isNumeric(QString) const;
    bool isDate(QString);
    void recollectData(int) const;
public:
    Controller();
public slots:

    /* MainWindow slots */
    void UpperInsert();
    void LowerInsert();
    void LeftInsert();
    void RightInsert();
    void TableReset();
    void RowReset();
    void ColumnReset();
    void SelectionReset();
    void RowDelete();
    void ColumnDelete();
    void LeftAlign();
    void CenterAlign();
    void RightAlign();
    void SpinBox();
    void SetTextSize();
    void TabClose(int);

    /* File Managment */
    void openFile();
    void saveFile();
    void saveACopy();
    void newTab();

    /* App Managment */
    void mainWindowCloseEvent();

    /*Chart section slots*/
    void BarChartCreation();
    void CandleStickChartCreation();
    void LineChartCreation();
    void PieChartCreation();
    void AreaChartCreation();

    /*Real-Time Chart Changes*/
    void pickTitle();
    void pickSeries();
    void ChartRefresh(int, int);
};

#endif // CONTROLLER_H
