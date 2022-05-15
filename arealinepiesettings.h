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
    AreaLinePieSettings(QWidget * = nullptr);
    AreaLinePieSettings(Flags type, QWidget * = nullptr);

    void setDataRangeTag(QString);
    QPair <QPair<int , int>, QPair<int, int>> getDataRange() const;
    QString getDataRangeTag() const;

    void setLabelsTag(QString);
    QPair <QPair<int , int>, QPair<int, int>> getLabelsRange() const;
    QString getLabelsTag() const;

    bool getParseMethod() const;
private:
    QLabel* _DataRange;
    QLabel* _Labels;
    QButtonGroup* _ParseMethod;
};

#endif // AREALINEPIESETTINGS_H
