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
    void setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getOpeningPricesRange() const;
    void setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getClosingPricesRange() const;
    void setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getLowestPricesRange() const;
    void setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair<QPair<int, int>, QPair<int, int>> getHighestPricesRange() const;
    virtual void setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesRange() const;
    virtual void refresh(QTableWidget*) const;

    virtual QJsonObject toJSON() const;
    virtual void fromJSON(const QJsonObject&);
private:
    QLabel* _OpeningPrices;
    QLabel* _ClosingPrices;
    QLabel* _LowestPrices;
    QLabel* _HighestPrices;
    QLabel* _Categories;
};

#endif // CANDLESTICKSETTINGS_H
