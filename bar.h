#ifndef BAR_H
#define BAR_H

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
protected:
    virtual void refresh();
public:
    Bar(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
};

#endif // BAR_H
