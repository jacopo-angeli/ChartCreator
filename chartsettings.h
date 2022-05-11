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
    Chart *_Chart;
private:
    QChartView *_ChartView;

    QLabel *_Title;
    QComboBox * _Color;
public:
    ChartSettings(QWidget* = nullptr);
    QChart* getChart();

    void setTitleTag(QString = "");
    QString getTitleTag() const;
};

#endif // CHARTSETTINGS_H
