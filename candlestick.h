#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#include "chart.h"

class CandleStick : public Chart
{
    Q_OBJECT
private:
    QList<double> _openingPrices;
    QList<double> _closingPrices;
    QList<double> _highestPrices;
    QList<double> _lowestPrices;
    QList<QString> _categories;
    void refresh();
public:
    CandleStick(QGraphicsItem* =nullptr);
    virtual void setSeries(QTableWidget*, const QModelIndexList&, Flags =Flags::ROW);
    virtual void clearData();
    void setOpeningPrices(QTableWidget*, const QModelIndexList&);
    void clearOpeningPrices();
    void setClosingPrices(QTableWidget*, const QModelIndexList&);
    void clearClosingPrices();
    void setLowestPrices(QTableWidget*, const QModelIndexList&);
    void clearLowestPrices();
    void setHighestPrices(QTableWidget*, const QModelIndexList&);
    void clearHighestPrices();
    void setCategories(QTableWidget*, const QModelIndexList&);
    void clearCategories();
};

#endif // CANDLESTICK_H
