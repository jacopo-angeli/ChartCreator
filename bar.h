#ifndef BAR_H
#define BAR_H

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
public:
    Bar(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearSeries();
};

#endif // BAR_H
