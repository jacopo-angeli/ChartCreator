#include "../hFiles/bar.h"
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

Bar::Bar(QWidget* brain): Chart(brain),_axisX(new QBarCategoryAxis()),_axisY(new QValueAxis()),_Values(QList<QList<double>>()),_Labels(QList<QString>()), _Categories(QList<QString>()){
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignRight);
    addAxis(_axisX, Qt::AlignBottom);
    addAxis(_axisY, Qt::AlignLeft);
}

void Bar::setSeries(QTableWidget* table, const QModelIndexList & indexes, Flags parseDirection){
    //Una line per riga/colonna a seconda del parseDirection
    //Se trovo un elemento indefinito creo una nuova line
    clearData();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                QList<double> set = QList<double>();
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != ""){
                        set.append(item->text().toDouble()>0 ? item->text().toDouble() : 0);
                    }else
                        set.append(0);
                }
                _Values.append(set);
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                QList<double> set = QList<double>();
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != ""){
                        set.append(item->text().toDouble()>0 ? item->text().toDouble() : 0);
                    }else
                        set.append(0);
                }
                _Values.append(set);
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    refresh();
}

void Bar::clearData(){
    foreach(QList<double> list, _Values)
        list.clear();
    _Values.clear();
    removeAllSeries();
}

void Bar::setLabels(QTableWidget* table, const QModelIndexList &indexes, Flags parseDirection){
    //Riempio labels/* con tante Stringhe quante solo le celle selezionate e se una delle celle è vuota o non piena metto Line x
    clearLabels();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item) _Labels.append(item->text());
                    else _Labels.append("");
                }
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item) _Labels.append(item->text());
                    else _Labels.append("");
                }
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    refresh();
}

void Bar::clearLabels(){
    _Labels.clear();
    refresh();
}
void Bar::clearCategories(){
    _Categories.clear();
    refresh();
}

void Bar::setCategories(QTableWidget* table, const QModelIndexList &indexes, Flags parseDirection){
    clearCategories();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                int itemCount=0;
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="")
                        _Categories.append(item->text());
                    else
                        _Categories.append("Categories " + QString::number(itemCount++));
                }
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                int itemCount=0;
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="")
                        _Categories.append(item->text());
                    else
                        _Categories.append("Categories " + QString::number(itemCount++));
                }
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    refresh();
}

void Bar::refresh(){
    removeAllSeries();
    QBarSeries* barSeries = new QBarSeries();
    int setNumber=0, catNumber=0;
    double max=INT_MIN;
    foreach(QList<double> list, _Values){
        QBarSet* barSet = new QBarSet((setNumber < _Labels.count() ? _Labels[setNumber++] : QString("Set " + QString::number(setNumber++))));
        foreach(double val, list){
            *barSet << val;
            max=std::max(max, val);
        }
        catNumber = std::max(barSet->count(), catNumber);
        barSeries->append(barSet);
    }
    addSeries(barSeries);
    QStringList categories;
    for(int i=0; i<catNumber; i++){
        if(i<_Categories.count())
            categories << _Categories[i];
        else
            categories << "Categories" + QString::number(i);
    }
    _axisX->clear();
    _axisX->append(categories);
    barSeries->attachAxis(_axisX);
    _axisY->setRange(0,max*1.10);
    barSeries->attachAxis(_axisY);
}
