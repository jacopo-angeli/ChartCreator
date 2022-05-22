#ifndef BAR_H
#define BAR_H

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
protected:
    virtual void refresh();
public:
    Bar(QWidget* =nullptr,QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearLabels();
};

#endif // BAR_H
