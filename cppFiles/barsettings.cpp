#include "../hFiles/barsettings.h"
BarSettings::BarSettings(QWidget * parent): AreaLinePieSettings(parent), _Categories(new QLabel("Unset"))
{
    QHBoxLayout * hor1=new QHBoxLayout();
    QPushButton * btn1=new QPushButton("PICK");
    btn1->setFixedWidth(120);
    connect(btn1, SIGNAL(clicked()), parent, SLOT(pickCategories()));
    QLabel* txt1=new QLabel("Categories");
    txt1->setFixedWidth(120);

    hor1->addWidget(txt1);
    hor1->addWidget(btn1);
    hor1->addWidget(_Categories);

    _Chart = new Bar(parent);
    _ChartView->setChart(_Chart);
    static_cast<QVBoxLayout*>(_Settings->layout())->addLayout(hor1);
}

BarSettings::~BarSettings(){
    delete _Categories;
}

void BarSettings::setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> pos){
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
    JsonObj["Type"]="Bar";
    JsonObj["CategoriesRange"]=_Categories->text();
    return JsonObj;
}

void BarSettings::fromJSON(const QJsonObject & chartJSON){
    AreaLinePieSettings::fromJSON(chartJSON);
    if(chartJSON["CategoriesRange"].toString() != "Unset")
        setCategoriesRange(tagToPairPair(chartJSON["CategoriesRange"].toString()));
}

void BarSettings::refresh(QTableWidget * table) const{
    AreaLinePieSettings::refresh(table);
    QPair<QPair<int,int>, QPair<int,int>> range = getCategoriesRange();
    if(range.first.first>0){
        QModelIndexList userSelection = table->selectionModel()->selectedIndexes();
        table->clearSelection();
        table->setRangeSelected(QTableWidgetSelectionRange(range.first.first-1, range.first.second-1, range.second.first-1, range.second.second-1), true);
        QModelIndexList indexes = table->selectionModel()->selectedIndexes();
        table->clearSelection();
        if(userSelection.size()>0) table->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
        static_cast<Bar*>(getChart())->setCategories(table, indexes, getParseMethod());
    }
}
