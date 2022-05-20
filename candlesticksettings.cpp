#include "candlesticksettings.h"
#include "candlestick.h"
CandleStickSettings::CandleStickSettings(QWidget* parent) : ChartSettings(parent), _OpeningPrices(new QLabel("Unset")), _ClosingPrices(new QLabel("Unset")), _LowestPrices(new QLabel("Unset")), _HighestPrices(new QLabel("Unset")), _Categories(new QLabel("Unset")){
    //layouts
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();

    //buttons
    QPushButton* btn1=new QPushButton("PICK");
    btn1->setFixedWidth(120);
    connect(btn1, SIGNAL(clicked()), parent, SLOT(pickOpeningPrices()));
    QPushButton* btn2=new QPushButton("PICK");
    btn2->setFixedWidth(120);
    connect(btn2, SIGNAL(clicked()), parent, SLOT(pickClosingPrices()));
    QPushButton* btn3=new QPushButton("PICK");
    btn3->setFixedWidth(120);
    connect(btn3, SIGNAL(clicked()), parent, SLOT(pickLowestPrices()));
    QPushButton* btn4=new QPushButton("PICK");
    btn4->setFixedWidth(120);
    connect(btn4, SIGNAL(clicked()), parent, SLOT(pickHighestPrices()));
    QPushButton* btn5=new QPushButton("PICK");
    btn5->setFixedWidth(120);
    connect(btn5, SIGNAL(clicked()), parent, SLOT(pickCategories()));

    //text labels

    QLabel* txt1=new QLabel("Opening Prices");
    QLabel* txt2=new QLabel("Closing Prices");
    QLabel* txt3=new QLabel("Lowest Prices");
    QLabel* txt4=new QLabel("Highest Prices");
    QLabel* txt5=new QLabel("Categories");

    txt1->setFixedWidth(120);
    txt2->setFixedWidth(120);
    txt3->setFixedWidth(120);
    txt4->setFixedWidth(120);
    txt5->setFixedWidth(120);

    //setting layout
    hor1->addWidget(txt1);
    hor1->addWidget(btn1);
    hor1->addWidget(_OpeningPrices);

    hor2->addWidget(txt2);
    hor2->addWidget(btn2);
    hor2->addWidget(_ClosingPrices);

    hor3->addWidget(txt3);
    hor3->addWidget(btn3);
    hor3->addWidget(_LowestPrices);

    hor4->addWidget(txt4);
    hor4->addWidget(btn4);
    hor4->addWidget(_HighestPrices);

    hor5->addWidget(txt5);
    hor5->addWidget(btn5);
    hor5->addWidget(_Categories);

    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor2);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor3);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor4);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor5);

    _Chart = new CandleStick();
    _ChartView->setChart(_Chart);
    _ChartView->setRenderHint(QPainter::Antialiasing);
}

void CandleStickSettings::setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=tag=QString("{( "+QString::number(pos.first.first)+ " , " +QString::number(pos.first.second)+" )->( "+ QString::number(pos.second.first)+ " , " + QString::number(pos.second.second) + " )}");
    }
    else
    {
        tag=("Unset");
    }
    _OpeningPrices->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getOpeningPricesRange() const{
    QString tag = _OpeningPrices->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void CandleStickSettings::setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=tag=QString("{( "+QString::number(pos.first.first)+ " , " +QString::number(pos.first.second)+" )->( "+ QString::number(pos.second.first)+ " , " + QString::number(pos.second.second) + " )}");
    }
    else
    {
        tag=("Unset");
    }
    _ClosingPrices->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getClosingPricesRange() const{
    QString tag = _ClosingPrices->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void CandleStickSettings::setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=tag=QString("{( "+QString::number(pos.first.first)+ " , " +QString::number(pos.first.second)+" )->( "+ QString::number(pos.second.first)+ " , " + QString::number(pos.second.second) + " )}");
    }
    else
    {
        tag=("Unset");
    }
    _LowestPrices->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getLowestPricesRange() const{
    QString tag = _LowestPrices->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void CandleStickSettings::setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=QString("{( "+QString::number(pos.first.first)+ " , " +QString::number(pos.first.second)+" )->( "+ QString::number(pos.second.first)+ " , " + QString::number(pos.second.second) + " )}");
    }
    else
    {
        tag=("Unset");
    }
    _HighestPrices->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getHighestPricesRange() const{
    QString tag = _HighestPrices->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

void CandleStickSettings::setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=QString("{( "+QString::number(pos.first.first)+ " , " +QString::number(pos.first.second)+" )->( "+ QString::number(pos.second.first)+ " , " + QString::number(pos.second.second) + " )}");
    }
    else
    {
        tag=("Unset");
    }
    _Categories->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > CandleStickSettings::getCategoriesRange() const{
    QString tag = _Categories->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

QJsonObject CandleStickSettings::toJSON() const{
     QJsonObject JsonObj = ChartSettings::toJSON();
     JsonObj["Type"]="CandleStick";
     JsonObj["OpeningPricesRange"]=_OpeningPrices->text();
     JsonObj["ClosingPricesRange"]=_ClosingPrices->text();
     JsonObj["LowestPricesRange"]=_LowestPrices->text();
     JsonObj["HighestPricesRange"]=_HighestPrices->text();
     JsonObj["CategoriesRange"]=_Categories->text();
     return JsonObj;
}

void CandleStickSettings::fromJSON(const QJsonObject& chartJSON){

    ChartSettings::fromJSON(chartJSON);
    if(chartJSON["CategoriesRange"].toString() != "Unset")
        setCategoriesRange(tagToPairPair(chartJSON["CategoriesRange"].toString()));
    if(chartJSON["ClosingPricesRange"].toString() != "Unset")
        setClosingPricesRange(tagToPairPair(chartJSON["ClosingPricesRange"].toString()));
    if(chartJSON["OpeningPricesRange"].toString() != "Unset")
        setOpeningPricesRange(tagToPairPair(chartJSON["OpeningPricesRange"].toString()));
    if(chartJSON["HighestPricesRange"].toString() != "Unset")
        setHighestPricesRange(tagToPairPair(chartJSON["HighestPricesRange"].toString()));
    if(chartJSON["LowestPricesRange"].toString() != "Unset")
        setLowestPricesRange(tagToPairPair(chartJSON["LowestPricesRange"].toString()));
}
