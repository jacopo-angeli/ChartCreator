#ifndef PIE_H
#define PIE_H

#include "chart.h"
class Pie : public Chart
{
    Q_OBJECT
public:
    Pie(QGraphicsItem* = nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearSeries();
};

#endif // PIE_H
