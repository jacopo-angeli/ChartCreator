#include "candlesticksettings.h"
#include "candlestick.h"
CandleStickSettings::CandleStickSettings(QWidget* parent) : ChartSettings(parent), _OpeningPrices(new QLabel("Opening Prices")), _ClosingPrices(new QLabel("Closing Prices")), _BottomPrices(new QLabel("Bottom Prices")), _LowestPrices(new QLabel("Lowest Prices")), _HighestPrices(new QLabel("Highest Prices")), _Categories(new QLabel("Categories"))
{

    //layouts
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();
    QHBoxLayout * hor6=new QHBoxLayout();

    //buttons

    QPushButton* btn1=new QPushButton("PICK");
    btn1->setMaximumHeight(50);
    btn1->setMaximumWidth(250);

    QPushButton* btn2=new QPushButton("PICK");
    btn2->setMaximumHeight(50);
    btn2->setMaximumWidth(250);

    QPushButton* btn3=new QPushButton("PICK");
    btn3->setMaximumHeight(50);
    btn3->setMaximumWidth(250);

    QPushButton* btn4=new QPushButton("PICK");
    btn4->setMaximumHeight(50);
    btn4->setMaximumWidth(250);

    QPushButton* btn5=new QPushButton("PICK");
    btn5->setMaximumHeight(50);
    btn5->setMaximumWidth(250);

    QPushButton* btn6=new QPushButton("PICK");
    btn6->setMaximumHeight(50);
    btn6->setMaximumWidth(250);

    //text labels

    QLabel* txt1=new QLabel("text");
    txt1->setMaximumHeight(50);
    txt1->setMaximumWidth(250);

    QLabel* txt2=new QLabel("text");
    txt2->setMaximumHeight(50);
    txt2->setMaximumWidth(250);

    QLabel* txt3=new QLabel("text");
    txt3->setMaximumHeight(50);
    txt3->setMaximumWidth(250);

    QLabel* txt4=new QLabel("text");
    txt4->setMaximumHeight(50);
    txt4->setMaximumWidth(250);

    QLabel* txt5=new QLabel("text");
    txt5->setMaximumHeight(50);
    txt5->setMaximumWidth(250);


    QLabel* txt6=new QLabel("text");
    txt6->setMaximumHeight(50);
    txt6->setMaximumWidth(250);

    //setting layout
    hor1->addWidget(_OpeningPrices);
    hor1->addWidget(btn1);
    hor1->addWidget(txt1);

    hor2->addWidget(_ClosingPrices);
    hor2->addWidget(btn2);
    hor2->addWidget(txt2);

    hor3->addWidget(_BottomPrices);
    hor3->addWidget(btn3);
    hor3->addWidget(txt3);

    hor4->addWidget(_LowestPrices);
    hor4->addWidget(btn4);
    hor4->addWidget(txt4);

    hor5->addWidget(_HighestPrices);
    hor5->addWidget(btn5);
    hor5->addWidget(txt5);

    hor6->addWidget(_Categories);
    hor6->addWidget(btn6);
    hor6->addWidget(txt6);

    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor2);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor3);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor4);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor5);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor6);

    _Chart = new CandleStick();
    _ChartView->setChart(_Chart);
}
