#ifndef PIE_H
#define PIE_H

#include "chart.h"
class Pie : public Chart
{
    Q_OBJECT
private:
    QList<double> _Data;
    QList<QString> _Labels;
protected:
    virtual void refresh();
public:
    Pie(QWidget* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    void clearLabels();
    virtual void clearData();
};

#endif // PIE_H
