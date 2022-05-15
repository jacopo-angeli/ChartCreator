#include "arealinepiesettings.h"
#include "area.h"
#include "line.h"
#include "pie.h"
AreaLinePieSettings::AreaLinePieSettings(QWidget * parent): ChartSettings(parent), _DataRange(new QLabel("Unset")), _Labels(new QLabel("Unset")), _ParseMethod(new QButtonGroup(_Settings)){
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();

    QPushButton* btn1=new QPushButton("PICK");
    btn1->setFixedWidth(120);
    QPushButton* btn2=new QPushButton("PICK");
    btn2->setFixedWidth(120);

    QRadioButton* row=new QRadioButton("Row Parsing");
    row->setFixedWidth(120);
    QRadioButton* col=new QRadioButton("Colum Parsing");
    row->setFixedWidth(120);
    col->click(); //segno checked per evitare
    _ParseMethod->addButton(row); //con questo li maneggio con i signal
    _ParseMethod->addButton(col); //successivamente aggiungendoli al layout singolarmente e poi a _Settings ne gestisco la grafica

    QLabel* txt1=new QLabel("Data Range");
    txt1->setFixedWidth(120);
    QLabel* txt2=new QLabel("Labels");
    txt2->setFixedWidth(120);

    //setting layout
    hor1->addWidget(txt1);
    hor1->addWidget(btn1);
    hor1->addWidget(_DataRange);

    hor2->addWidget(txt2);
    hor2->addWidget(btn2);
    hor2->addWidget(_Labels);

    QLabel* parseMethodLabel=new QLabel("Parse Direction");
    parseMethodLabel->setFixedWidth(120);
    hor3->addWidget(parseMethodLabel);
    hor3->addWidget(row); //parse method
    hor3->addWidget(col);

    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor2);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor3);
}

AreaLinePieSettings::AreaLinePieSettings(Flags type, QWidget* parent): AreaLinePieSettings(parent){
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

void AreaLinePieSettings:: setDataRangeTag(QString q){
    _DataRange->setText(q);
}

bool AreaLinePieSettings::getParseMethod() const{
    if(_ParseMethod->checkedButton()->text() == "Row Parsing") return false;
    else return true;
}

QPair <QPair<int , int>, QPair<int, int>> AreaLinePieSettings::getDataRange() const{
    QString tag = getDataRangeTag();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

QString AreaLinePieSettings::getDataRangeTag() const{
    return _DataRange->text();
}

QString AreaLinePieSettings::getLabelsTag() const{
    return _Labels->text();
}
