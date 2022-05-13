#ifndef AREALINEPIESETTINGS_H
#define AREALINEPIESETTINGS_H
#include "chartsettings.h"
#include "flags.h"
#include <QObject>
#include <QtCharts>

class AreaLinePieSettings : public ChartSettings
{
     Q_OBJECT
public:
    AreaLinePieSettings(Chart * =nullptr, QWidget * = nullptr);
    AreaLinePieSettings(Flags type);
    void setDataRangeTag(QString);
    QString getDataRangeTag() const;
    QPair <QPair<int , int>, QPair<int, int>> getDataRange() const;
    //TODO GetParseMethod don't know return type
    private:
    QLabel* _DataRange;
    QLabel* _labels;
    QButtonGroup* _ParseMethod;
};

#endif // AREALINEPIESETTINGS_H
