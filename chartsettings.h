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
    QTableWidget *_ValueTab;
    QGroupBox *_Settings;
    QChartView *_ChartView;
public:
    ChartSettings(QWidget* = nullptr);
public slots:
    void createPushd();

};

#endif // CHARTSETTINGS_H
