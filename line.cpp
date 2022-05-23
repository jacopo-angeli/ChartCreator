#include "line.h"

Line::Line(QGraphicsItem* parent): Chart(parent)
{

}

void Line::setSeries(QTableWidget * table, const QModelIndexList& indexes, Flags parseDirection)
{
    switch(parseDirection)
    {
    case(Flags::ROW):{
          for(int i=indexes.last().row(); i>=indexes.first().row();i--)
          {
              QLineSeries *series = new QLineSeries();
              int pC=0;
              for(int j=indexes.first().column(); j<=indexes.last().column();j++)
              {
                  QTableWidgetItem *item=table->item(i,j);
                  if(item && item->text()!="")
                  {
                      series->append(++pC,item->text().toInt());
                  }
              }
              //if(series->count()>0) series.append(series);
              //else delete series;
          }
        }
        break;
    case(Flags::COLUMN):
      {
         for(int j=indexes.last().column(); j>=indexes.first().column(); j--)
         {
             QLineSeries *series = new QLineSeries();
             int pC=0;
             for(int i=indexes.first().row(); i<=indexes.last().row();i++){
                 QTableWidgetItem* item = table->item(i, j);
                 if(item) *series << QPointF(++pC,item->text().toInt());
             }
             //if(series->count()>0)
         }
      }
        break;
    }
}

void Line::clearData()
{

}

void Line::refresh()
{

}
