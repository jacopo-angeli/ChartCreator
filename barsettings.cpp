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

}

QPair<QPair<int, int>, QPair<int, int> > BarSettings::getCategoriesRange() const{

}

QJsonObject BarSettings::toJSON() const{

}

void BarSettings::fromJSON(const QJsonObject &)
{

}
