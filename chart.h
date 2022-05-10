#ifndef CHART_H
#define CHART_H
#include <QObject>
#include <QtCharts>

class Chart : public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem* =nullptr);
};

#endif // CHART_H
