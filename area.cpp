#include "area.h"

Area::Area(QGraphicsItem* parent): Chart(parent), _series(QList<QLineSeries*>()){
    setAnimationOptions(QChart::AllAnimations);
}

void Area::setSeries(QTableWidget* table, const QModelIndexList& indexes, Flags parseDirection){
    QLineSeries *series = new QLineSeries();
    switch(parseDirection){
        case(Flags::ROW):{
            int pC=0;
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item) *series << QPointF(++pC,item->text().toInt());
                }
            }
        }
        break;
        case(Flags::COLUMN):{
            int pC=0;
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item) *series << QPointF(++pC,item->text().toInt());
                }
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    if(series->count() > 0) _series.append(series);
    refresh();
}

void Area::clearSeries(){
    _series.clear();
}

void Area::refresh(){
    removeAllSeries();
    QPen pen(0x059605);
    pen.setWidth(3);
    for(auto it=_series.begin(); it!=_series.end(); it++){
        QAreaSeries *series = new QAreaSeries(*it);
        (*it)->setPen(pen);
        addSeries(series);
    }
    createDefaultAxes();
}

