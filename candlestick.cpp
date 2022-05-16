#include "candlestick.h"
CandleStick::CandleStick(QGraphicsItem * parent): Chart(parent), _openingPrices(QList<double>()), _closingPrices(QList<double>()), _highestPrices(QList<double>()), _lowestPrices(QList<double>()), _categories(QList<QString>()){
//    1435708800000 126.90 126.94 125.99 126.60
//    1435795200000 126.69 126.69 126.69 126.69
//    1436140800000 124.85 126.23 124.85 126.00
//    1436227200000 125.89 126.15 123.77 125.69
//    1436313600000 124.64 124.64 122.54 122.54
//    1436400000000 123.85 124.06 119.22 120.07
//    1436486400000 121.94 123.85 121.21 123.28
//    1436745600000 125.03 125.76 124.32 125.66
//    1436832000000 126.04 126.37 125.04 125.61
//    1436918400000 125.72 127.15 125.58 126.82
//    1437004800000 127.74 128.57 127.35 128.51
//    1437091200000 129.08 129.62 128.31 129.62
//    1437350400000 130.97 132.97 130.70 132.07
//    1437436800000 132.85 132.92 130.32 130.75
//    1437523200000 121.99 125.50 121.99 125.22
//    1437609600000 126.20 127.09 125.06 125.16
//    1437696000000 125.32 125.74 123.90 124.50
//    1437955200000 123.09 123.61 122.12 122.77
//    1438041600000 123.38 123.91 122.55 123.38
//    1438128000000 123.15 123.50 122.27 122.99
//    1438214400000 122.32 122.57 121.71 122.37
//    1438300800000 122.60 122.64 120.91 121.30
    setAnimationOptions(QChart::SeriesAnimations);
}

void CandleStick::refresh(){
    if(int categoriesSize = _categories.size()){
        removeAllSeries();
        int i=0;
        QCandlestickSeries *series = new QCandlestickSeries();
        QStringList categories;
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));
        while(i<categoriesSize && i<_openingPrices.size() && i<_closingPrices.size() && i<_highestPrices.size() && i<_lowestPrices.size()){
            qDebug() << "Serie aggiunta";
            QCandlestickSet *candlestickSet = new QCandlestickSet();
            candlestickSet->setOpen(_openingPrices[i]);
            candlestickSet->setClose(_closingPrices[i]);
            candlestickSet->setLow(_lowestPrices[i]);
            candlestickSet->setHigh(_highestPrices[i]);
            series->append(candlestickSet);
            series->setName(_categories[i]);
            i++;
        }
        series->setIncreasingColor(QColor(Qt::green));
        series->setDecreasingColor(QColor(Qt::red));
        addSeries(series);
        createDefaultAxes();

        QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(axes(Qt::Horizontal).at(0));
        axisX->setCategories(categories);

        QValueAxis *axisY = qobject_cast<QValueAxis *>(axes(Qt::Vertical).at(0));
        axisY->setMax(axisY->max() * 1.05);
        axisY->setMin(axisY->min() * 0.5);
    }return;
}
void CandleStick::changeData(QList<QTableWidgetItem *>){

}

void CandleStick::setOpeningPrices(QTableWidget* table, const QModelIndexList& indexes){
    //Pulisco _openingPrice e lo riempio con i nuovi valori
    _openingPrices.clear();
    for(int i=0; i<indexes.size(); i++){
        QTableWidgetItem* item=table->item(indexes[i].row(), indexes[i].column());
        if(item){
            qDebug() << item->text().toDouble();
            _openingPrices.append(item->text().toDouble());
        }else{
            qDebug() << "INT_MIN";
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
            qDebug() << item->text().toDouble();
            _closingPrices.append(item->text().toDouble());
        }else{
            qDebug() << "INT_MIN";
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
                qDebug() << item->text().toDouble();
                _lowestPrices.append(item->text().toDouble());
            }else{
                qDebug() << "INT_MIN";
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
                qDebug() << item->text().toDouble();
                _highestPrices.append(item->text().toDouble());
            }else{
                qDebug() << "INT_MIN";
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
            qDebug() << item->text().toDouble();
            _categories.append(item->text());
        }else{
            qDebug() << "Stringa vuota";
            _categories.append("");
        }
    }
    refresh();
}

void CandleStick::clearCategories(){

}
