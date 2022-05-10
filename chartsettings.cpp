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
ChartSettings::ChartSettings(QWidget * parent) : QWidget(parent), _Settings(new QGroupBox(this)), _ChartView(new QChartView(this)), _Chart(new QChart()), _Title(new QLabel("Unset")), _Description(new QLabel("Unset")), _DataRange(new QLabel("Unset")){

    QLineSeries *series1 = new QLineSeries();
    QLineSeries *series2 = new QLineSeries();
    *series1 << QPointF(1, 50) << QPointF(2, 70) << QPointF(3, 40) << QPointF(4, 35) << QPointF(5, 61);
    *series2 << QPointF(1, 55) << QPointF(2, 75) << QPointF(3, 45) << QPointF(4, 40) << QPointF(5, 66);
    series1->setName("Line1");
    _Chart->addSeries(series1);
        _Chart->addSeries(series2);
        _Chart->createDefaultAxes();
        _Chart->setTitle("Simple line chart example");
    QBarSet * set0 = new QBarSet("");
            QBarSeries *series111= new QBarSeries();
    series111->append(set0);
    _ChartView->setChart(_Chart);

    QVBoxLayout* mainL = new QVBoxLayout;

    QVBoxLayout* vert= new QVBoxLayout();
    QVBoxLayout* vert2= new QVBoxLayout();
    //layout orizzontale
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();
    QHBoxLayout * hor6=new QHBoxLayout();
    QHBoxLayout * hor7=new QHBoxLayout();
    QHBoxLayout * hor8=new QHBoxLayout();
    QHBoxLayout * hor9=new QHBoxLayout();
    QHBoxLayout * hor10=new QHBoxLayout();
    QHBoxLayout * foot=new QHBoxLayout();
    //labels
    QLabel* _lab1=new  QLabel("Title");
    QLabel* _lab2=new  QLabel("Description");
    QLabel* _lab3=new  QLabel("Data Series");
    QLabel* _lab4=new  QLabel("Opening Prices");
    QLabel* _lab5=new  QLabel("Closing Prices");
    QLabel* _lab6=new  QLabel("Bottom Prices");
    QLabel* _lab7=new  QLabel("Lowest Prices");
    QLabel* _lab8=new  QLabel("Highest Prices");
    QLabel* _lab9=new  QLabel("Categories");
    QLabel* _lab10=new  QLabel("COlor Palette");
    //buttons

    QPushButton* _btn1=new QPushButton("PICK", this);
    QPushButton* _btn2=new QPushButton("PICK", this);
    QPushButton* _btn3=new QPushButton("PICK", this);
    QPushButton* _btn4=new QPushButton("PICK");
    QPushButton* _btn5=new QPushButton("PICK");
    QPushButton* _btn6=new QPushButton("PICK");
    QPushButton* _btn7=new QPushButton("PICK");
    QPushButton* _btn8=new QPushButton("PICK");
    QPushButton* _btn9=new QPushButton("PICK");
    QPushButton* _btn10=new QPushButton("PICK");
    QPushButton* _help=new QPushButton("HELP");

    //Lables
    QLabel* _txt4=new QLabel("Unset");
    QLabel* _txt5=new QLabel("Unset");
    QLabel* _txt6=new QLabel("Unset");
    QLabel* _txt7=new QLabel("Unset");
    QLabel* _txt8=new QLabel("Unset");
    QLabel* _txt9=new QLabel("Unset");
    //setting layout
    //line1
    hor1->addWidget(_lab1);
    hor1->addWidget(_btn1);
    connect(_btn1, SIGNAL(clicked()), parent->parent(), SLOT(pickTitle()));
    hor1->addWidget(_Title);
    vert2->addLayout(hor1);
    //line2
    hor2->addWidget(_lab2);
    hor2->addWidget(_btn2);
    hor2->addWidget(_Description);
    vert2->addLayout(hor2);

    //line3
    hor3->addWidget(_lab3);
    hor3->addWidget(_btn3);
    connect(_btn3, SIGNAL(clicked()), parent->parent(), SLOT(pickSeries()));
    hor3->addWidget(_DataRange);
    vert2->addLayout(hor3);
    //line4
    hor4->addWidget(_lab4);
    hor4->addWidget(_btn4);
    hor4->addWidget(_txt4);
    vert2->addLayout(hor4);
    //line5
    hor5->addWidget(_lab5);
    hor5->addWidget(_btn5);
    hor5->addWidget(_txt5);
    vert2->addLayout(hor5);
    //line6
    hor6->addWidget(_lab6);
    hor6->addWidget(_btn6);
    hor6->addWidget(_txt6);
    vert2->addLayout(hor6);
    //line7
    hor7->addWidget(_lab7);
    hor7->addWidget(_btn7);
    hor7->addWidget(_txt7);
    vert2->addLayout(hor7);
    //line8
    hor8->addWidget(_lab8);
    hor8->addWidget(_btn8);
    hor8->addWidget(_txt8);
    vert2->addLayout(hor8);
    //line9
    hor9->addWidget(_lab9);
    hor9->addWidget(_btn9);
    hor9->addWidget(_txt9);
    vert2->addLayout(hor9);
    //line10
    hor10->addWidget(_lab10);
    hor10->addWidget(_btn10);
    vert2->addLayout(hor10);

    _Settings->setLayout(vert2);
    vert->addWidget(_Settings);

    //footer
    foot->addWidget(_help);
    foot->setAlignment(Qt::AlignBottom | Qt::AlignRight);
    vert->addLayout(foot);

    _ChartView->setMinimumWidth(600);
    mainL->addWidget(_ChartView);
    mainL->addLayout(vert);

    setLayout(mainL);
    setWindowFlags(Qt::Window);

}

QChart *ChartSettings::getChart(){
    return _Chart;
}

void ChartSettings::setTitleTag(QString text){
    if(text=="") _Title->setText("Unset");
    else _Title->setText(text);
}

QString ChartSettings::getTitleTag() const{
    return _Title->text();
}

void ChartSettings::setDataRangeTag(QString newTag){
    if(newTag!="") _DataRange->setText(newTag);
    else _DataRange->setText("Unset");
}

QString ChartSettings::getDataRangeTag() const{
    return _DataRange->text();
}

QPair<QPair<int, int>, QPair<int, int>> ChartSettings::getDataRange() const{
    QString tag = getDataRangeTag();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}


