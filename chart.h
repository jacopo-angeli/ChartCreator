#ifndef CHART_H
#define CHART_H
#include <QObject>
#include <QtCharts>

class Chart : public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>)=0;
};

#endif // CHART_H
