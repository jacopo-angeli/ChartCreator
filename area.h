#ifndef AREA_H
#define AREA_H
#include "chart.h"
#include "flags.h"

class Area : public Chart
{
    Q_OBJECT
public:
    Area(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
private:
    QList<QLineSeries*> _series;
    void refresh();
};

#endif // AREA_H
