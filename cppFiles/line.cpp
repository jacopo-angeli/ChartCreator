#include "../hFiles/line.h"

Line::Line(QWidget* brain): Chart(brain), _Values(QList<QList<double>>()), _Labels(QList<QString>()){
    legend()->setVisible(true);
    legend()->setAlignment(Qt::AlignRight);
}

void Line::setSeries(QTableWidget * table, const QModelIndexList& indexes, Flags parseDirection){
    //Una line per riga/colonna a seconda del parseDirection
    //Se trovo un elemento indefinito creo una nuova line
    clearData();
    switch(parseDirection){
        case(Flags::ROW):{
            for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                QList<double> line = QList<double>();
                for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        line.append(item->text().toDouble());
                }
                if(line.count()>1) _Values.append(line);
            }
        }
        break;
        case(Flags::COLUMN):{
            for(int j=indexes.first().column(); j<=indexes.last().column();j++){
                QList<double> line = QList<double>();
                for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                    QTableWidgetItem* item = table->item(i, j);
                    if(item && item->text() != "")
                        //chek if its convetible to double
                        line.append(item->text().toDouble());
                }
                if(line.count()>1) _Values.append(line);
            }
        }
        break;
        default:
            //Lancia eccezioni
        break;
    }
    refresh();
}

void Line::clearData(){
    foreach(QList<double> list, _Values)
        list.clear();
    _Values.clear();
}

void Line::setLabels(QTableWidget *table, const QModelIndexList & indexes, Flags parseDirection){
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

void Line::clearLabels(){
    _Labels.clear();
}

void Line::refresh(){
    double min = INT_MAX, max = INT_MIN;
    int lineCount=0;
    removeAllSeries();
    foreach(QList<double> list, _Values){
        int pointCount=0;
        QLineSeries* series = new QLineSeries();
        foreach(double val, list){
            if(val > INT_MIN){
                min=std::min(min, val);
                max=std::max(max, val);
                series->append(QPoint(pointCount+1, val));
                if(lineCount<_Labels.count())
                    series->setName(_Labels[lineCount]);
                else
                    series->setName("Line "+QString::number(lineCount+1));
                pointCount++;
            }
        }
        lineCount++;
        addSeries(series);
    }
    createDefaultAxes();

    if(axes(Qt::Vertical).count()>0) {
        QValueAxis *axisY = qobject_cast<QValueAxis *>(axes(Qt::Vertical).at(0));
        axisY->setMax(max * 1.02);
        axisY->setMin(min * (min < 0 ? 1.02 : 0.90));
    }
}
