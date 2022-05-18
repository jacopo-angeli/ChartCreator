#include "barsettings.h"
BarSettings::BarSettings(QWidget * parent): AreaLinePieSettings(parent), _Categories(new QLabel("Unset"))
{
    QHBoxLayout * hor1=new QHBoxLayout();
    QPushButton * btn1=new QPushButton("PICK");
    btn1->setFixedWidth(120);
    QLabel* txt1=new QLabel("Categories");
    txt1->setFixedWidth(120);

    hor1->addWidget(txt1);
    hor1->addWidget(btn1);
    hor1->addWidget(_Categories);

    _Chart = new Bar();
    _ChartView->setChart(_Chart);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
}

void BarSettings::setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> pos){
    QString tag=QString();
    if((pos.first.first)>0)
    {
        tag=QString("{("+QString::number(pos.first.first)+ "," +QString::number(pos.first.second)+")->("+ QString::number(pos.second.first)+ "," + QString::number(pos.second.second));
    }
    else
    {
        tag=("Unset");
    }
    _Categories->setText(tag);
}

QPair<QPair<int, int>, QPair<int, int> > BarSettings::getCategoriesRange() const{
    QString tag = _Categories->text();
    QList<QString> tagSplitted = tag.split(' ');
    if(tag!="Unset"){
        QPair<int, int> fP = QPair<int, int>(tagSplitted[1].toInt(),tagSplitted[3].toInt());
        QPair<int, int> lP = QPair<int, int>(tagSplitted[5].toInt(),tagSplitted[7].toInt());
        return QPair<QPair<int, int>, QPair<int, int>>(fP, lP);
    }
    return QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0));
}

QJsonObject BarSettings::toJSON() const{
    QJsonObject JsonObj = AreaLinePieSettings::toJSON();
    JsonObj["Type"]="BarSettings";
    JsonObj["CategoriesRange"]=_Categories->text();
    return JsonObj;
}

void BarSettings::fromJSON(const QJsonObject & chartJSON){
    AreaLinePieSettings::fromJSON(chartJSON);
    if(chartJSON["CategoriesRange"].toString() != "Unset")
        setCategoriesRange(tagToPairPair(chartJSON["CategoriesRange"].toString()));
}
