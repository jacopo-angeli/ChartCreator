#ifndef LINE_H
#define LINE_H

#include "chart.h"
class Line : public Chart
{
    Q_OBJECT
public:
    Line(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
};

#endif // LINE_H
