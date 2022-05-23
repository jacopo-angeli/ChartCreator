#include "area.h"
#include<QAreaSeries>
Area::Area(QWidget* brain, QGraphicsItem* parent): Chart(brain, parent), _values(QList<QList<double>>()), _areaSeries(QList<QAreaSeries*>()){
    setAnimationOptions(QChart::SeriesAnimations);
//    legend()->hide();
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
            for(int i=indexes.last().row(); i>=indexes.first().row();i--){
                QList<double> row = QList<double>();
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="") row.append(item->text().toInt());
                }
                if(row.count() > 0) _values.append(row);
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.last().column(); j>=indexes.first().column();j--){
                QList<double> column = QList<double>();
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="") column.append(item->text().toInt());
                }
                if(column.count() > 0) _values.append(column);
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    refresh();
}

void Area::clearData(){
    // It will only destroy pointers, not the objects behind them (same with removeAt() of course). Delete needs to be called explicitely on each item or, as already said, qDeleteAll() can be used.
    for(auto it = _values.begin(); it!=_values.end(); it++){
        it->clear();
    }
    _values.clear();
}

void Area::setLabels(QTableWidget *, const QModelIndexList &, Flags )
{

}

void Area::clearLabels()
{

}

void Area::refresh(){
    if(series().length()>0) {
        qDebug() << "removeAllSeries";
        removeAllSeries();
    }
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
            addSeries(series);
        }
    }
    createDefaultAxes();
}

