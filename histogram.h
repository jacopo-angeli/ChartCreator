#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "chart.h"
class Histogram : public Chart
{
    Q_OBJECT
public:
    Histogram(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);
};

#endif // HISTOGRAM_H
