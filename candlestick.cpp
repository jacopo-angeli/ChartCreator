#include "candlestick.h"
CandleStick::CandleStick(QGraphicsItem * parent): Chart(parent), _openingPrices(QList<double>()), _closingPrices(QList<double>()), _highestPrices(QList<double>()), _lowestPrices(QList<double>()), _categories(QList<QString>()){
    setAnimationOptions(QChart::SeriesAnimations);
    legend()->hide();
}

void CandleStick::setSeries(QTableWidget *, const QModelIndexList &, Flags)
{

}

void CandleStick::clearData()
{

}

void CandleStick::refresh(){
    int categoriesSize = _categories.size();
    if(categoriesSize>0){
        double max=INT_MIN, min=INT_MAX;
        removeAllSeries();
        int i=0;
        QCandlestickSeries *series = new QCandlestickSeries();
        QStringList categories;
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));
        while(i<categoriesSize && i<_openingPrices.size() && i<_closingPrices.size() && i<_highestPrices.size() && i<_lowestPrices.size()){
            QCandlestickSet *candlestickSet = new QCandlestickSet();
            candlestickSet->setOpen(_openingPrices[i]);
            max = std::max(max,_openingPrices[i]);
            min = std::min(min,_openingPrices[i]);
            candlestickSet->setClose(_closingPrices[i]);
            max = std::max(max,_closingPrices[i]);
            min = std::min(min,_closingPrices[i]);
            candlestickSet->setLow(_lowestPrices[i]);
            max = std::max(max,_lowestPrices[i]);
            min = std::min(min,_lowestPrices[i]);
            candlestickSet->setHigh(_highestPrices[i]);
            max = std::max(max,_highestPrices[i]);
            min = std::min(min,_highestPrices[i]);
            series->append(candlestickSet);
            categories << _categories[i];
            i++;
        }
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));
        addSeries(series);
        createDefaultAxes();

        QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(axes(Qt::Horizontal).at(0));
        axisX->setCategories(categories);

        QValueAxis *axisY = qobject_cast<QValueAxis *>(axes(Qt::Vertical).at(0));
        axisY->setMax(max * 1.1);
        axisY->setMin(min * (min < 0 ? 1.1 : 0.5));
        //se min è negativo problemi
    }return;
}

void CandleStick::setOpeningPrices(QTableWidget* table, const QModelIndexList& indexes){
    //Pulisco _openingPrice e lo riempio con i nuovi valori
    _openingPrices.clear();
    for(int i=0; i<indexes.size(); i++){
        QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
        if(item){
            _openingPrices.append(item->text().toDouble());
        }else{
            _openingPrices.append(INT_MIN);
        }
    }
    refresh();
}

void CandleStick::clearOpeningPrices(){

}

void CandleStick::setClosingPrices(QTableWidget* table, const QModelIndexList& indexes){
    _closingPrices.clear();
    for(int i=0; i<indexes.size(); i++){
        QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
        if(item){
            _closingPrices.append(item->text().toDouble());
        }else{
            _closingPrices.append(INT_MIN);
        }
    }
    refresh();
}

void CandleStick::clearClosingPrices(){

}

void CandleStick::setLowestPrices(QTableWidget* table, const QModelIndexList& indexes){
    _lowestPrices.clear();
    for(int i=0; i<indexes.size(); i++){
            QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
            if(item){
                _lowestPrices.append(item->text().toDouble());
            }else{
                _lowestPrices.append(INT_MIN);
            }

        }
    refresh();
}

void CandleStick::clearLowestPrices(){

}

void CandleStick::setHighestPrices(QTableWidget* table, const QModelIndexList& indexes){
    _highestPrices.clear();
    for(int i=0; i<indexes.size(); i++){
            QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
            if(item){
                _highestPrices.append(item->text().toDouble());
            }else{
                _highestPrices.append(INT_MIN);
            }
        }
    refresh();
}

void CandleStick::clearHighestPrices(){

}

void CandleStick::setCategories(QTableWidget *table, const QModelIndexList& indexes){
    _categories.clear();
    for(int i=0; i<indexes.size(); i++){
        QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
        if(item){
            _categories.append(item->text());
        }else{
            _categories.append("");
        }
    }
    refresh();
}

void CandleStick::clearCategories(){

}
