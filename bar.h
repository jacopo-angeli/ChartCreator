#ifndef BAR_H
#define BAR_H

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
private:
    QList<QList<double>> _Values;
    QList<QString> _Labels;
    QList<QString> _Categories;
protected:
    virtual void refresh();
public:
    Bar(QWidget* =nullptr,QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearLabels();
    void clearCategories();
    void setCategories(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
};

#endif // BAR_H
