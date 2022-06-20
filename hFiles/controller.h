#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "chartselection.h"
#include "chartsettings.h"
#include "../hFiles/flags.h"

#include <QObject>
#include <QVector>
#include <QWidget>
#include <QDesktopServices>

class Controller : public QWidget{
    Q_OBJECT
private:
    QWidget* guideWindow;
    MainWindow* _MainWindow;
    QMap<QString, QString> _ActiveFiles;
    void lastSessionRestore();
    bool fileSave(int, QString = "") const;
    void fileOpen(QString = "");
    bool isInRange(QPair<int,int>, QPair<QPair<int,int>,QPair<int,int>>);
    bool isInRange(QPair<int,int>, QPair<int,int>);
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
    void ChartTabClose(int);

    /* File Managment */
    void openFile();
    void saveFile();
    void saveACopy();
    void newTab();

    /* App Managment */
    void mainWindowCloseEvent();
    void chartCreationGuide();
    void closeGuideWindow();

    /*Chart section slots*/
    void BarChartCreation();
    void CandleStickChartCreation();
    void LineChartCreation();
    void PieChartCreation();
    void AreaChartCreation();

    /*Chart*/
    void pickTitle();
    void pickOpeningPrices();
    void pickClosingPrices();
    void pickLowestPrices();
    void pickHighestPrices();
    void pickDataRange();
    void pickLabels();
    void pickCategories();
    void ChartRefresh(int, int);
    void parseMethodChange(QAbstractButton*);
    void themeChanged(int);
    void chartReset();
    void sliceStandOut();
};

#endif // CONTROLLER_H
