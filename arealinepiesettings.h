#ifndef AREALINEPIESETTINGS_H
#define AREALINEPIESETTINGS_H
#include "chartsettings.h"
#include <QObject>
#include <QtCharts>

class AreaLinePieSettings : public ChartSettings
{
     Q_OBJECT
public:
    AreaLinePieSettings(QWidget * = nullptr);
private:
    QLabel* _DataRange;
    QLabel* _labels;
    QButtonGroup* _ParseMethod;
};

#endif // AREALINEPIESETTINGS_H
