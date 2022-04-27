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
    QTabWidget* _Tab;
    QTableWidget* _Table;
    QSpinBox* _TxtDim;

    int _ValidatorFlag;

    int getMaxMenuSize(QMenu*);
    int getTextSize();
    bool TableParser(const QString&);
public:
    MainWindow(QWidget * =nullptr);
    void addRow(Flags = Flags::TOP);
    void addColumn(Flags = Flags::LEFT);
    void clearTable();
    void clearContent(Flags = Flags::SELECTION);
    void deleteContent(Flags = Flags::ROW);
    void textAlign(Flags = Flags::LEFT);
    void setSpinBox();
    void setTextSize();
};

#endif // MAINWINDOW_H
