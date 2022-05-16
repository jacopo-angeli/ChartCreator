#ifndef CANDLESTICKSETTINGS_H
#define CANDLESTICKSETTINGS_H
#include "chartsettings.h"
#include <QObject>
#include <QtCharts>

class CandleStickSettings : public ChartSettings
{
    Q_OBJECT
public:
    CandleStickSettings(QWidget * = nullptr);
    void setOpeningPricesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getOpeningPricesPosition() const;
    void setClosingPricesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getClosingPricesPositions() const;
    void setLowestPricesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getLowestPricesPositions() const;
    void setHighestPricesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getHighestPricesPositions() const;
    virtual void setCategoriesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesPositions() const;
private:
    QLabel* _OpeningPrices;
    QLabel* _ClosingPrices;
    QLabel* _LowestPrices;
    QLabel* _HighestPrices;
    QLabel* _Categories;
};

#endif // CANDLESTICKSETTINGS_H
