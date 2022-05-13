#ifndef BARSETTINGS_H
#define BARSETTINGS_H
#include "arealinepiesettings.h"
#include <QObject>
#include <QtCharts>
class BarSettings: public AreaLinePieSettings
{
    Q_OBJECT
public:
    BarSettings(Chart*,QWidget* =nullptr);
    void setCategoriesTag(QString);
    QString getCategoriesTag() const;
private:
    QLabel* _Categories;
};

#endif // BARSETTINGS_H
