#ifndef BAR_H
#define BAR_H

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
public:
    Bar(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);
};

#endif // BAR_H
