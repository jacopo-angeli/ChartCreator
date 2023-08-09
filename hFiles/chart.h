#ifndef CHART_H
#define CHART_H
#include <QObject>
#include <QtCharts>
#include <iostream>
#include "flags.h"

class Chart : public QChart
{
    Q_OBJECT
protected:
    QWidget* _controller;
    virtual void refresh() =0;
public:
    Chart(QWidget* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW)=0;
    virtual void clearData()=0;
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW)=0;
    virtual void clearLabels()=0;
    virtual ~Chart() =default;
};

#endif // CHART_H
