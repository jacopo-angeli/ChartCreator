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

    void setDataRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair <QPair<int , int>, QPair<int, int>> getDataRange() const;

    void setLabels(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    QPair <QPair<int , int>, QPair<int, int>> getLabelsRange() const;

    virtual void setCategoriesPositions(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesPositions() const;

    bool getParseMethod() const;
private:
    QLabel* _DataRange;
    QLabel* _Labels;
    QButtonGroup* _ParseMethod;
};

#endif // AREALINEPIESETTINGS_H
