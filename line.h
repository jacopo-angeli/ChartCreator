#ifndef LINE_H
#define LINE_H

#include "chart.h"
class Line : public Chart
{
    Q_OBJECT
public:
    Line(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);
};

#endif // LINE_H
