#ifndef AREA_H
#define AREA_H
#include "chart.h"

class Area : public Chart
{
    Q_OBJECT
public:
    Area(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);
};

#endif // AREA_H
