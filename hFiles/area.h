#ifndef AREA_H
#define AREA_H
#include "chart.h"
#include "flags.h"

class Area : public Chart
{
    Q_OBJECT
protected:
    virtual void refresh();
public:
    Area(QWidget* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearLabels();
private:
    QList<QLineSeries*> _Values;
    QList<QString> _Labels;
};

#endif // AREA_H
