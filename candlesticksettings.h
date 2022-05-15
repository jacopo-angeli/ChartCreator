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
    void setOpeningPricesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getOpeningPricesPosition() const;
    void setClosingPricesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getClosingPricesPositions() const;
    void setBottomPricesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getBottomPricesPositions() const;
    void setLowestPricesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getLowestPricesPositions() const;
    void setHighestPricesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getHighestPricesPositions() const;
    void setCategoriesTag(QString = "");
    QPair<QPair<int, int>, QPair<int, int>> getCategoriesPositions() const;
private:
    QLabel* _OpeningPrices;
    QLabel* _ClosingPrices;
    QLabel* _BottomPrices;
    QLabel* _LowestPrices;
    QLabel* _HighestPrices;
    QLabel* _Categories;
};

#endif // CANDLESTICKSETTINGS_H
