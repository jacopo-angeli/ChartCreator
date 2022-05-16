#ifndef BARSETTINGS_H
#define BARSETTINGS_H
#include "arealinepiesettings.h"
#include "bar.h"
#include <QObject>
#include <QtCharts>
class BarSettings: public AreaLinePieSettings
{
    Q_OBJECT
public:
    BarSettings(QWidget* =nullptr);
    virtual void setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0)));
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesRange() const;
private:
    QLabel* _Categories;
};

#endif // BARSETTINGS_H
