#include "area.h"

Area::Area(QWidget* brain,QGraphicsItem* parent): Chart(brain, parent), _values(QList<QList<double>>()){
    setAnimationOptions(QChart::SeriesAnimations);
    legend()->hide();
}
/**
 * @brief Area::setSeries
 * @param table
 * @param indexes : lista di indici della tabella indici che partono da 0;
 * @param parseDirection
 */
void Area::setSeries(QTableWidget* table, const QModelIndexList& indexes, Flags parseDirection){
    clearData();
    switch(parseDirection){
        case(Flags::ROW):{

        }
        case(Flags::COLUMN):{

        }
        break;
        default:
        break;
    }
}

void Area::clearData(){
    // It will only destroy pointers, not the objects behind them (same with removeAt() of course). Delete needs to be called explicitely on each item or, as already said, qDeleteAll() can be used.
    removeAllSeries();
    _values.clear();
}

void Area::setLabels(QTableWidget *, const QModelIndexList &, Flags){

}

void Area::clearLabels(){

}

void Area::refresh(){
    removeAllSeries();
    QPen pen(0x059605);
    pen.setWidth(3);
    for(auto it=_values.begin(); it!=_values.end(); it++){
        if((*it).count() > 1){
            QLineSeries *series = new QLineSeries();
            int xVal = 0;
            for(auto init = (*it).begin() ; init !=(*it).end() ; init++){
                //init iterator per QList<double>
                series->append(xVal, *init);
                xVal++;
            }
            addSeries(new QAreaSeries(series));
        }
    }
    createDefaultAxes();
}

