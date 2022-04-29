#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "flags.h"

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
    QTabWidget* _Tabs;
    QSpinBox* _TxtDim;

    int getMaxMenuSize(QMenu*);
    int getTextSize();
    bool TableParser(const QString&);
public:
    MainWindow(QWidget* =nullptr);
    void addRow(Flags = Flags::TOP);
    void addColumn(Flags = Flags::LEFT);
    void clearTable();
    void clearContent(Flags = Flags::SELECTION);
    void deleteContent(Flags = Flags::ROW);
    void textAlign(Flags = Flags::LEFT);
    void setSpinBox(int);
    void setTextSize(int);

    int getSpinValue();
    QString getCurrentTabName();
    QString getTabName(int);
    QTableWidget* getFullTable(int);
    int getRowCount(int);
    int getColumnCount(int);

    void closeTab(int);

    void openFile(QString,QTableWidget*);
    void newTab();
};

#endif // MAINWINDOW_H
