#include "chartsettings.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QWidgetAction>
#include <QStringList>
#include <QColorDialog>
#include <QtCharts>
#include <QWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
ChartSettings::ChartSettings(Chart * chart,QWidget * parent) : QWidget(parent),  _Settings(new QGroupBox(this)), _ChartView(new QChartView(this)), _Chart(chart), _Title(new QLabel("Unset")), _Color(new QComboBox())
{
    _ChartView->setChart(_Chart);
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QVBoxLayout * main=new QVBoxLayout();

    main->addWidget(_ChartView);

    QPushButton* btn1=new QPushButton("PICK");
    btn1->setMaximumHeight(50);
    btn1->setMaximumWidth(250);

    QPushButton* btn2=new QPushButton("PICK");
    btn2->setMaximumHeight(50);
    btn2->setMaximumWidth(250);

    QLabel* txt1=new QLabel("text");
    txt1->setMaximumHeight(50);
    txt1->setMaximumWidth(250);

    QLabel* txt2=new QLabel("text");
    txt2->setMaximumHeight(50);
    txt2->setMaximumWidth(250);

    //horizontal
    hor1->addWidget(_Title);
    hor1->addWidget(btn1);
    hor1->addWidget(txt1);
    hor2->addWidget(_Color);
    hor2->addWidget(btn2);
    hor2->addWidget(txt2);
    _Settings->setLayout(hor1);
    _Settings->setLayout(hor2);
    main->addWidget(_Settings);
}


