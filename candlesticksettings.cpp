#include "candlesticksettings.h"
#include "candlestick.h"
CandleStickSettings::CandleStickSettings(QWidget* parent) : ChartSettings(parent), _Chart(new CandleStick), _OpeningPrices(new QLabel("Unset")), _ClosingPrices(new QLabel("Unset")), _BottomPrices(new QLabel("Unset")), _LowestPrices(new QLabel("Unset")), _HighestPrices(new QLabel("Unset")),_Categories(new QLabel("Unset"))
{

    //layouts
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();
    QHBoxLayout * hor6=new QHBoxLayout();

    QVBoxLayout * _imp=new QVBoxLayout(); //layout per contenere la chartview
    QVBoxLayout * _main=new QVBoxLayout(); //layout per contenere vista e settings



    //buttons

    QPushButton* _btn1=new QPushButton("PICK");
    _btn1->setMaximumHeight(50);
    _btn1->setMaximumWidth(250);

    QPushButton* _btn2=new QPushButton("PICK");
    _btn2->setMaximumHeight(50);
    _btn2->setMaximumWidth(250);

    QPushButton* _btn3=new QPushButton("PICK");
    _btn3->setMaximumHeight(50);
    _btn3->setMaximumWidth(250);

    QPushButton* _btn4=new QPushButton("PICK");
    _btn4->setMaximumHeight(50);
    _btn4->setMaximumWidth(250);

    QPushButton* _btn5=new QPushButton("PICK");
    _btn5->setMaximumHeight(50);
    _btn5->setMaximumWidth(250);

    QPushButton* _btn6=new QPushButton("PICK");
    _btn6->setMaximumHeight(50);
    _btn6->setMaximumWidth(250);

    //text labels

    QLabel* _txt1=new QLabel("text");
    _txt1->setMaximumHeight(50);
    _txt1->setMaximumWidth(250);

    QLabel* _txt2=new QLabel("text");
    _txt2->setMaximumHeight(50);
    _txt2->setMaximumWidth(250);

    QLabel* _txt3=new QLabel("text");
    _txt3->setMaximumHeight(50);
    _txt3->setMaximumWidth(250);

    QLabel* _txt4=new QLabel("text");
    _txt4->setMaximumHeight(50);
    _txt4->setMaximumWidth(250);

    QLabel* _txt5=new QLabel("text");
    _txt5->setMaximumHeight(50);
    _txt5->setMaximumWidth(250);


    QLabel* _txt6=new QLabel("text");
    _txt6->setMaximumHeight(50);
    _txt6->setMaximumWidth(250);

}
