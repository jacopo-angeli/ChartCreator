#include "bar.h"

Bar::Bar(QWidget* brain, QGraphicsItem* parent): Chart(brain, parent), _Values(QList<QList<double>>()), _Labels(QList<QString>()), _Categories(QList<QString>()){
    setAnimationOptions(QChart::SeriesAnimations);
    legend()->setAlignment(Qt::AlignRight);
}

void Bar::setSeries(QTableWidget* table, const QModelIndexList & indexes, Flags parseDirection){
    //Una line per riga/colonna a seconda del parseDirection
    //Se trovo un elemento indefinito creo una nuova line
    clearData();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                QList<double> bars = QList<double>();
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        bars.append(item->text().toDouble());
                    else
                        bars.append(0);
                }
                if(bars.count()>1) _Values.append(bars);
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                QList<double> bars = QList<double>();
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        bars.append(item->text().toDouble());
                    else
                        bars.append(0);
                }
                if(bars.count()>1) _Values.append(bars);
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
}

void Bar::setLabels(QTableWidget* table, const QModelIndexList &indexes, Flags parseDirection){
    //Riempio labels/* con tante Stringhe quante solo le celle selezionate e se una delle celle è vuota o non piena metto Line x
    clearLabels();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                int itemCount=0;
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="")
                        _Labels.append(item->text());
                    else
                        _Labels.append("Set " + QString::number(itemCount++));
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
                        _Labels.append(item->text());
                    else
                        _Labels.append("Set " + QString::number(itemCount++));
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
}

void Bar::clearCategories(){
    _Categories.clear();
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
    int setCount=0, elNumber=0;
    double min=INT_MAX, max=INT_MIN;
    QBarSeries * series = new QBarSeries();
    foreach(QList<double> set, _Values){
        QBarSet *barSet = new QBarSet((setCount<_Labels.count() ? _Labels[setCount] : QString("Set "+QString::number(setCount+1))));
        foreach(double val, set){
            min=std::min(min, val);
            max=std::max(max, val);
            barSet->append(val);
        }
        if(elNumber==0) elNumber=barSet->count();
        series->append(barSet);
        setCount++;
    }
    addSeries(series);
    QList<QString> categories;
    for(int i=0; i<elNumber; i++){
        if(i<_Categories.count())
            categories.append(_Categories[i]);
        else
            categories.append("Category " + QString::number(i+1));
    }
    createDefaultAxes();
//    if(axes(Qt::Vertical).count()>0) {
//        QValueAxis *axisY = qobject_cast<QValueAxis *>(axes(Qt::Vertical).at(0));
//        axisY->setRange(min,max*1.2);
//        series->attachAxis(axisY);
//    }
//    if(axes(Qt::Horizontal).count()>0) {
//        QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(axes(Qt::Vertical).at(0));
//        axisX->append(categories);
//    }
}
