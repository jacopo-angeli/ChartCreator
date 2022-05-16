#ifndef CHARTSETTINGS_H
#define CHARTSETTINGS_H
#include "chart.h"
#include <QObject>
#include <QWidget>
#include <QWidgetAction>
#include <QStringList>
#include <QColorDialog>
#include <QtCharts>
#include <QWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>


class ChartSettings : public QWidget
{
        Q_OBJECT
protected:
    QGroupBox *_Settings;
    QChartView *_ChartView;
    Chart *_Chart;
private:
    QLabel *_Title;
    QComboBox * _Color;
public:
    ChartSettings(QWidget* = nullptr);
    QChart* getChart();

    void setTitlePosition(QPair<int, int> = QPair<int, int>(0,0));
    QPair<int, int> getTitlePosition() const;

    virtual void setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0))) =0;
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesRange() const =0;
};

#endif // CHARTSETTINGS_H
