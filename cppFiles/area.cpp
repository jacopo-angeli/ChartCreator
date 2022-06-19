#include "../hFiles/area.h"

Area::Area(QWidget* brain): Chart(brain), _Values(QList<QLineSeries*>()), _Labels(QList<QString>()){
//    setAnimationOptions(QChart::SeriesAnimations);
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignRight);
}
/**
 * @brief Area::setSeries
 * @param table
 * @param indexes : lista di indici della tabella indici che partono da 0;
 * @param parseDirection
 */
void Area::setSeries(QTableWidget* table, const QModelIndexList& indexes, Flags parseDirection){
    foreach(QLineSeries* lineSeries, _Values)
        delete lineSeries;
    _Values.clear();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                QLineSeries* line = new QLineSeries();
                int pointCounter=0;
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        line->append(QPointF(pointCounter++, item->text().toDouble()));
                    else
                        line->append(QPointF(pointCounter++, 0));
                }
                if(line->count()>1) _Values.append(line);
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                QLineSeries* line = new QLineSeries();
                int pointCounter=0;
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        line->append(QPointF(pointCounter++, item->text().toDouble()));
                    else
                        line->append(QPointF(pointCounter++, 0));
                }
                if(line->count()>1) _Values.append(line);
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
    foreach(QLineSeries* lineSeries, _Values)
        delete lineSeries;
    _Values.clear();
    refresh();
}

void Area::setLabels(QTableWidget* table, const QModelIndexList &indexes, Flags parseDirection){
    _Labels.clear();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                int itemCount=0;
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!="")
                        _Labels.append(item->text());
                    else
                        _Labels.append("Line " + QString::number(itemCount++));
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
                        _Labels.append("Line " + QString::number(itemCount++));
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

void Area::clearLabels(){
    _Labels.clear();
    refresh();
}

void Area::refresh(){
    removeAllSeries();
    int areaCount=0;
    foreach(QLineSeries* lineSeries, _Values){
        QAreaSeries* areaSeries = new QAreaSeries(lineSeries);
        if(areaCount<_Labels.count())
            areaSeries->setName(_Labels[areaCount++]);
        else
            areaSeries->setName("Area " + QString::number(++areaCount));
        addSeries(areaSeries);
    }
    createDefaultAxes();
}

