#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "graphwindow.h"

#include <QWidget>
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
    QTableWidget *_Table;
    QWidget *_GraphWindow;
    QSpinBox *_TxtDim;

    int _ValidatorFlag;

    int getMaxMenuSize(QMenu*);
    void ClearTable();
    bool TableParser(const QString&);
public:
    MainWindow(QWidget * =nullptr);
public slots:
    void UpperInsert();
    void LowerInsert();
    void RightInsert();
    void LeftInsert();
    void TableResetAlert();
    void OpenGraphWindow();
    void ClearSelection();
    void ClearRow();
    void ClearColumn();
    void DeleteColumn();
    void DeleteRow();
    void CellValidator(int, int);

    void NewWorkSheet();
    void SaveCsvCopy();

    void LeftAlign();
    void CenterAlign();
    void RightAlign();
    void SetTextSize();
    void SpinBoxRefresh();
};

#endif // MAINWINDOW_H
