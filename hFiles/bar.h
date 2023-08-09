#ifndef BAR_H
#define BAR_H
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include "chart.h"
class Bar : public Chart
{
    Q_OBJECT
private:
    QBarCategoryAxis* _axisX;
    QValueAxis* _axisY;
    QList<QList<double>> _Values;
    QList<QString> _Labels;
    QList<QString> _Categories;
protected:
    virtual void refresh();
public:
    Bar(QWidget* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearData();
    virtual void setLabels(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
    virtual void clearLabels();
    void clearCategories();
    void setCategories(QTableWidget*, const QModelIndexList&, Flags = Flags::ROW);
};

#endif // BAR_H
