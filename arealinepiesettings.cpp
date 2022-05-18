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
    connect(btn1, SIGNAL(clicked()), parent, SLOT(pickDataRange()));
    QPushButton* btn2=new QPushButton("PICK");
    btn2->setFixedWidth(120);

    QRadioButton* row=new QRadioButton("Row Parsing");
    row->setFixedWidth(150);
    row->setIcon(QIcon("../OOPPROJECT/icons/RowParse.png"));
    QRadioButton* col=new QRadioButton("Colum Parsing");
    col->setFixedWidth(150);
    col->setIcon(QIcon("../OOPPROJECT/icons/ColumnParse.png"));
    row->click(); //segno checked per evitare
    _ParseMethod->addButton(row); //con questo li maneggio con i signal
    _ParseMethod->addButton(col); //successivamente aggiungendoli al layout singolarmente e poi a _Settings ne gestisco la grafica
    connect(_ParseMethod, SIGNAL(buttonClicked(QAbstractButton*)), parent, SLOT(parseMethodChange(QAbstractButton*)));

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
    hor3->addStretch();

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
    _ChartView->setChart(_Chart);
    _ChartView->setRenderHint(QPainter::Antialiasing);
}

void AreaLinePieSettings:: setDataRange(QPair<QPair<int, int>, QPair<int, int>> pos){
    //Check se pos.first>0
        //crei la stringa
            // {( pos.first.first , pos.first.second )->( pos.second.first , pos.second.second )}
        //e setti il tag
    //settare il tag a "Unset" _Labels -> setText("Unset") (Controllare se è diverso da "Unset")
}

Flags AreaLinePieSettings::getParseMethod() const{
    if(_ParseMethod->checkedButton()->text() == "Row Parsing") return Flags::ROW;
    else return Flags::COLUMN;
}

QPair <QPair<int , int>, QPair<int, int>> AreaLinePieSettings::getDataRange() const{
    QString tag = _DataRange->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void AreaLinePieSettings::setLabelsRange(QPair<QPair<int, int>, QPair<int, int>> pos){
    //Check se pos.first>0
        //crei la stringa
            // {( pos.first.first , pos.first.second )->( pos.second.first , pos.second.second )}
        //e setti il tag
    //settare il tag a "Unset" _Labels -> setText("Unset") (Controllare se è diverso da "Unset")
}

QPair<QPair<int, int>, QPair<int, int>> AreaLinePieSettings::getLabelsRange() const{
    QString tag = _Labels->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void AreaLinePieSettings::setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>){}
QPair<QPair<int, int>, QPair<int, int> > AreaLinePieSettings::getCategoriesRange() const{
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

QJsonObject AreaLinePieSettings::toJSON() const{
    QJsonObject JsonObj = ChartSettings::toJSON();
    if(dynamic_cast<Pie*>(getChart())){
        JsonObj["type"]="Pie";
    }else if(dynamic_cast<Area*>(getChart())){
        JsonObj["type"]="Area";
    }else{
        JsonObj["type"]="Line";
    }
    JsonObj["DataRange"]=_DataRange->text();
    JsonObj["LabelsRange"]=_Labels->text();
    return JsonObj;
}

void AreaLinePieSettings::fromJSON(const QJsonObject& chartJSON){
    ChartSettings::fromJSON(chartJSON);
    if(chartJSON["CategoriesRange"].toString() != "Unset")
        setCategoriesRange(tagToPairPair(chartJSON["CategoriesRange"].toString()));
    if(chartJSON["DataRange"].toString() != "Unset")
        setDataRange(tagToPairPair(chartJSON["CategoriesRange"].toString()));
    if(chartJSON["LablesRange"].toString() != "Unset")
        setDataRange(tagToPairPair(chartJSON["LabRange"].toString()));
}
