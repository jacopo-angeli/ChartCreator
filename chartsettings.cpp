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
QJsonValue ChartSettings::getTitleJson() const{
    return _Title->text();
}

QJsonValue ChartSettings::getColorJson() const{
    return _Color->currentIndex();
}

ChartSettings::ChartSettings(QWidget * parent) : QWidget(parent),  _Settings(new QGroupBox(this)), _ChartView(new QChartView(this)), _Chart(nullptr), _Title(new QLabel("Unset")), _Color(new QComboBox()){
    QVBoxLayout * main=new QVBoxLayout();
    main->addWidget(_ChartView);
    //Buttons
    QHBoxLayout * hor0=new QHBoxLayout();
    QPushButton* btn00=new QPushButton("Reset");
    btn00->setFixedWidth(120);
    btn00->setFixedHeight(50);
    connect(btn00, SIGNAL(clicked()), parent, SLOT(chartReset()));
    QPushButton* btn01=new QPushButton("Guide");
    btn01->setFixedWidth(120);
    btn01->setFixedHeight(50);
    connect(btn01, SIGNAL(clicked()), parent, SLOT(chartCreationGuide()));
    hor0->addWidget(btn00);
    hor0->addWidget(btn01);
    hor0->addStretch();

    //Title Row
    QHBoxLayout * hor1=new QHBoxLayout();
    QLabel* txt1=new QLabel("Title");
    hor1->addWidget(txt1);
    QPushButton* btn1=new QPushButton("PICK");
    hor1->addWidget(btn1);
    connect(btn1, SIGNAL(clicked()), parent, SLOT(pickTitle()));
    hor1->addWidget(_Title);

    //Color Setting Row
    QHBoxLayout * hor2=new QHBoxLayout();
    QLabel* colorLabel=new QLabel("Color Palette");
    _Color->addItem("Default");
    _Color->addItem("Blue Cerulean");
    _Color->addItem("Dark");
    _Color->addItem("Brown Sand");
    _Color->addItem("Blue Natural");
    _Color->addItem("High Contrast");
    _Color->addItem("Blue Icy");
    _Color->addItem("Qt");
    connect(_Color, SIGNAL(currentIndexChanged(int)), parent, SLOT(themeChanged(int)));
    hor2->addWidget(colorLabel);
    hor2->addWidget(_Color);

    //Size Adjustments
    txt1->setFixedWidth(120);
    btn1->setFixedWidth(120);
    colorLabel->setFixedWidth(120);
    _Color->setFixedWidth(300);
    hor2->addStretch();

    QVBoxLayout * settingsLayout=new QVBoxLayout();

    settingsLayout->addLayout(hor0);
    settingsLayout->addLayout(hor2);
    settingsLayout->addLayout(hor1);
    _Settings->setLayout(settingsLayout);
    main->addWidget(_Settings);

    setLayout(main);
}
Chart* ChartSettings::getChart(){
    return _Chart;
}
void ChartSettings::setTitlePosition(QPair<int, int> pos){
//    QString cellPos = QString("(" + (QString::number(pos.first)) + ", " + (QString::number(pos.second)) + ")");
}
QPair<int, int> ChartSettings:: getTitlePosition() const{

}
void ChartSettings::setColorIndex(int index){
    if(index>0 && index<7)
        _Color->setCurrentIndex(index);
}
QPair<QPair<int, int>, QPair<int, int> > ChartSettings::tagToPair(QString tag){
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
};


//TODO GETCOLORPALETTE
