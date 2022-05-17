#ifndef CHART_H
#define CHART_H
#include <QObject>
#include <QtCharts>
#include "flags.h"

class Chart : public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW)=0;
    virtual void clearSeries()=0;
};

#endif // CHART_H
