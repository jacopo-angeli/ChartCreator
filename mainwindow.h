#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flags.h"
#include "chartselection.h"
#include "chartsettings.h"
#include "arealinepiesettings.h"
#include "candlesticksettings.h"
#include "barsettings.h"

#include <QJsonDocument>
#include <QWidget>
#include <QStandardPaths>
#include <QTextStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QFileDialog>
#include <QKeySequence>
#include <QMainWindow>
#include <QWindow>
#include <iostream>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QAction>
#include <QTableWidget>
#include <QSizePolicy>
#include <QMessageBox>
#include <QPushButton>
#include <QColor>
#include <QSpinBox>
#include <QFont>

class MainWindow : public QMainWindow{
   Q_OBJECT
private:
    QTabWidget* _Files;
    QSpinBox* _TxtDim;

    int getMaxMenuSize(QMenu*);
public:
    MainWindow(QWidget* =nullptr);
    void setSpinBox(int);

    int getFilePosition(QString);
    int getRowCount(int);
    int getColumnCount(int);
    int getSpinValue();
    int getCurrentTabIndex();
    int getCurrentChartTabIndex();
    int getChartNumber(int);
    QString getTabName(int =-1);
    QTableWidget* getFullTable(int);
    ChartSettings* getChartTab(int, int =-1);
    void setCurrentTabTitle(QString);

    void closeTab(int);
    void closeChartTab(int);

    void chartTypeSelected(Flags);
    void newTab();

    void closeEvent(QCloseEvent*);
signals:
    void closing();
};

#endif // MAINWINDOW_H
