#include "barsettings.h"
BarSettings::BarSettings(Chart * chart, QWidget * parent): AreaLinePieSettings(chart, parent), _Categories(new QLabel("Unset"))
{
    QHBoxLayout * hor1=new QHBoxLayout();
    QPushButton * btn1=new QPushButton();
    btn1->setMaximumHeight(50);
    btn1->setMaximumWidth(250);

    QLabel* txt1=new QLabel("text");
    txt1->setMaximumHeight(50);
    txt1->setMaximumWidth(250);

    hor1->addWidget(_Categories);
    hor1->addWidget(btn1);
    hor1->addWidget(txt1);

    _Settings->setLayout(hor1);
}
void BarSettings::setCategoriesTag(QString q)
{
    _Categories->setText(q);
}
QString BarSettings::getCategoriesTag() const
{
    return _Categories->text();
}
