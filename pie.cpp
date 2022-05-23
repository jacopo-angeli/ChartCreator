#include "pie.h"

Pie::Pie(QWidget* brain, QGraphicsItem* parent): Chart(brain, parent), _Data(QList<double>()), _Labels(QList<QString>()){
    setAnimationOptions(QChart::AllAnimations);
    legend()->show();
    legend()->setAlignment(Qt::AlignRight);
}

void Pie::setSeries(QTableWidget * table, const QModelIndexList & indexes, Flags parseDirection){
    clearData();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!=""){
                        //check if is a double
                        _Data.append(item->text().toDouble());
                    }
                }
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text()!=""){
                        //check if is a double
                        _Data.append(item->text().toDouble());
                    }
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

void Pie::setLabels(QTableWidget* table, const QModelIndexList& indexes, Flags parseDirection){
    clearLabels();
    switch(parseDirection){
        case(Flags::ROW):{
            int sliceCount = 1;
            for(int i=indexes.first().row(); i<=indexes.last().row(); i++){
                for(int j=indexes.first().column(); j<=indexes.last().column(); j++){
                    if(table->item(i,j) && table->item(i,j)->text() != "")
                        _Labels.append(table->item(i,j)->text());
                    else
                        _Labels.append("Slice" + QString::number(sliceCount));
                    sliceCount++;
                }
            }
        }
        break;
        case(Flags::COLUMN):{
            int sliceCount = 1;
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    if(table->item(i,j) && table->item(i,j)->text() != "")
                        _Labels.append(table->item(i,j)->text());
                    else
                        _Labels.append("Slice" + QString::number(sliceCount));
                    sliceCount++;
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

void Pie::clearLabels(){
    _Labels.clear();
    refresh();
}

void Pie::clearData(){
    _Data.clear();
    removeAllSeries();
}

void Pie::refresh(){
    removeAllSeries();
    QPieSeries *series = new QPieSeries();
    for(int i=0; i<_Data.count(); i++){
        if(_Data[i]){
            if(i<_Labels.count()){
                series->append(_Labels[i], _Data[i]);
            }else{
                series->append(QString("slice" + QString::number(i)), _Data[i]);
            }

        }
    }
    foreach(QPieSlice* slice, series->slices())
        connect(slice, SIGNAL(clicked()), _controller, SLOT(sliceStandOut()));
    addSeries(series);
}

