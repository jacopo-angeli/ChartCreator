#ifndef CANDLESTICK_H
#define CANDLESTICK_H
#include "chart.h"

class CandleStick : public Chart
{
    Q_OBJECT
public:
    CandleStick(QGraphicsItem* =nullptr);
    virtual void changeData(QList<QTableWidgetItem*>);


};

#endif // CANDLESTICK_H
