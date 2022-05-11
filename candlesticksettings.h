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
private:
    QLabel* _OpeningPrices;
    QLabel* _ClosingPrices;
    QLabel* _BottomPrices;
    QLabel* _LowestPrices;
    QLabel* _HighestPrices;
    QLabel* _Categories;
};

#endif // CANDLESTICKSETTINGS_H
