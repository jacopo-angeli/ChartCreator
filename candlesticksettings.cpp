#include "candlesticksettings.h"
#include "candlestick.h"
CandleStickSettings::CandleStickSettings(QWidget* parent) : ChartSettings(parent), _OpeningPrices(new QLabel("Unset")), _ClosingPrices(new QLabel("Unset")), _LowestPrices(new QLabel("Unset")), _HighestPrices(new QLabel("Unset")), _Categories(new QLabel("Unset")){
    //layouts
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();
    QHBoxLayout * hor6=new QHBoxLayout();

    //buttons
    QPushButton* btn1=new QPushButton("PICK");
    btn1->setFixedWidth(120);
    QPushButton* btn2=new QPushButton("PICK");
    btn2->setFixedWidth(120);
    QPushButton* btn3=new QPushButton("PICK");
    btn3->setFixedWidth(120);
    QPushButton* btn4=new QPushButton("PICK");
    btn4->setFixedWidth(120);
    QPushButton* btn5=new QPushButton("PICK");
    btn5->setFixedWidth(120);
    QPushButton* btn6=new QPushButton("PICK");
    btn6->setFixedWidth(120);

    //text labels

    QLabel* txt1=new QLabel("Opening Prices");
    QLabel* txt2=new QLabel("Closing Prices");
    QLabel* txt3=new QLabel("Bottom Prices");
    QLabel* txt4=new QLabel("Lowest Prices");
    QLabel* txt5=new QLabel("Highest Prices");
    QLabel* txt6=new QLabel("Categories");

    txt1->setFixedWidth(120);
    txt2->setFixedWidth(120);
    txt3->setFixedWidth(120);
    txt4->setFixedWidth(120);
    txt5->setFixedWidth(120);
    txt6->setFixedWidth(120);

    //setting layout
    hor1->addWidget(txt1);
    hor1->addWidget(btn1);
    hor1->addWidget(_OpeningPrices);

    hor2->addWidget(txt2);
    hor2->addWidget(btn2);
    hor2->addWidget(_ClosingPrices);

    hor4->addWidget(txt4);
    hor4->addWidget(btn4);
    hor4->addWidget(_LowestPrices);

    hor5->addWidget(txt5);
    hor5->addWidget(btn5);
    hor5->addWidget(_HighestPrices);

    hor6->addWidget(txt6);
    hor6->addWidget(btn6);
    hor6->addWidget(_Categories);

    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor2);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor3);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor4);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor5);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor6);

    _Chart = new CandleStick();
    _ChartView->setChart(_Chart);
}

void CandleStickSettings::setOpeningPricesPositions(QPair<QPair<int, int>, QPair<int, int> >)
{

}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getOpeningPricesPosition() const
{

}

void CandleStickSettings::setClosingPricesPositions(QPair<QPair<int, int>, QPair<int, int> >)
{

}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getClosingPricesPositions() const
{

}

void CandleStickSettings::setLowestPricesPositions(QPair<QPair<int, int>, QPair<int, int> >)
{

}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getLowestPricesPositions() const
{

}

void CandleStickSettings::setHighestPricesPositions(QPair<QPair<int, int>, QPair<int, int> >)
{

}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getHighestPricesPositions() const
{

}

void CandleStickSettings::setCategoriesPositions(QPair<QPair<int, int>, QPair<int, int> >)
{

}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getCategoriesPositions() const
{

}
