#include "arealinepiesettings.h"
#include "area.h"
#include "line.h"
#include "pie.h"
AreaLinePieSettings::AreaLinePieSettings(Chart * chart, QWidget * parent): ChartSettings(parent), _DataRange(new QLabel("Unset")), _labels(new QLabel("Unset")), _ParseMethod(new QButtonGroup(_Settings))
{
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();

    QPushButton* btn1=new QPushButton("PICK");
    btn1->setMaximumHeight(50);
    btn1->setMaximumWidth(250);

    QPushButton* btn2=new QPushButton("PICK");
    btn2->setMaximumHeight(50);
    btn2->setMaximumWidth(250);

    QPushButton* btn3=new QPushButton("PICK");
    btn3->setMaximumHeight(50);
    btn3->setMaximumWidth(250);

    QRadioButton* row=new QRadioButton("Row Parsing");
    QRadioButton* col=new QRadioButton("Colum Parsing");
    col->isChecked(); //segno checked per evitare

    _ParseMethod->addButton(row); //con questo li maneggio con i signal
    _ParseMethod->addButton(col); //successivamente aggiungendoli al layout singolarmente e poi a _Settings ne gestisco la grafica

    QLabel* txt1=new QLabel("text");
    txt1->setMaximumHeight(50);
    txt1->setMaximumWidth(250);

    QLabel* txt2=new QLabel("text");
    txt2->setMaximumHeight(50);
    txt2->setMaximumWidth(250);

    QLabel* txt3=new QLabel("text");
    txt3->setMaximumHeight(50);
    txt3->setMaximumWidth(250);
    //setting layout

    hor1->addWidget(_DataRange);
    hor1->addWidget(btn1);
    hor1->addWidget(txt1);

    hor2->addWidget(_labels);
    hor2->addWidget(btn2);
    hor2->addWidget(txt2);

    hor3->addWidget(row); //parse method
    hor3->addWidget(col);


    _Settings->setLayout(hor1);
    _Settings->setLayout(hor2);
    _Settings->setLayout(hor3);
}

AreaLinePieSettings::AreaLinePieSettings(Flags type, QWidget* parent): AreaLinePieSettings(nullptr, parent){
    switch(type){
        case (Flags::AREA):{
            _Chart = new Area();
        }
            break;
        case (Flags::LINES):{
            _Chart = new Line();
        }
            break;
        case (Flags::PIE):{
            _Chart = new Pie();
        }
        default:
            break;
    }
}

void AreaLinePieSettings:: setDataRangeTag(QString q)
{
    _DataRange->setText(q);
}

QString AreaLinePieSettings:: getDataRangeTag() const
{
    return _DataRange->text();
}
 //TODO METODO DI RITORNO CON I PAIR NON SO COME SI USANO


