#ifndef PIE_H
#define PIE_H

#include "chart.h"
class Pie : public Chart
{
    Q_OBJECT
public:
    Pie(QGraphicsItem* = nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);
};

#endif // PIE_H
