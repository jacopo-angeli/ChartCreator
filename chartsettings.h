#ifndef CHARTSETTINGS_H
#define CHARTSETTINGS_H

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
private:
    QGroupBox *_Settings;
    QChartView *_ChartView;
    QChart *_Chart;
    QLabel *_Title;
    QLabel *_Description;
    QLabel *_DataRange;
public:
    ChartSettings(QWidget* = nullptr);
    QChart* getChart();

    void setTitleTag(QString = "");
    QString getTitleTag() const;

    void setDataRangeTag(QString = "");
    QString getDataRangeTag() const;
    QPair<QPair<int, int>, QPair<int, int>> getDataRange() const;

    void recollect();
};

#endif // CHARTSETTINGS_H
