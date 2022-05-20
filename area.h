#ifndef AREA_H
#define AREA_H
#include "chart.h"
#include "flags.h"

class Area : public Chart
{
    Q_OBJECT
protected:
    virtual void refresh();
public:
    Area(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
private:
    QList<QList<double>> _values;
};

#endif // AREA_H
