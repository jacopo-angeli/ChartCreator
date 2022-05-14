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
ChartSettings::ChartSettings(QWidget * parent) : QWidget(parent),  _Settings(new QGroupBox(this)), _ChartView(new QChartView(this)), _Chart(nullptr), _Title(new QLabel("Title")), _Color(new QComboBox())
{
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QVBoxLayout * main=new QVBoxLayout();
    QVBoxLayout * settingsLayout=new QVBoxLayout();

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
    //Creare label per combobox
    hor2->addWidget(_Color);
    hor2->addWidget(btn2);
    hor2->addWidget(txt2);
    settingsLayout->addLayout(hor1);
    settingsLayout->addLayout(hor2);
    _Settings->setLayout(settingsLayout);
    main->addWidget(_Settings);

    //!!
    setLayout(main);
}
QChart* ChartSettings::getChart()
{
    return _ChartView->chart();
}

void ChartSettings::setTitleTag(QString q)
{
    _Title->setText(q);
}

QString ChartSettings:: getTitleTag() const
{
    return _Title->text();
}

//TODO GETCOLORPALETTE
