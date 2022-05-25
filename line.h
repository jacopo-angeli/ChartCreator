#ifndef LINE_H
#define LINE_H

#include "chart.h"
class Line : public Chart
{
    Q_OBJECT
private:
    QList<QList<double>> _Values;
    QList<QString> _Labels;
protected:
    virtual void refresh();
public:
    Line(QWidget* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearLabels();
};

#endif // LINE_H
