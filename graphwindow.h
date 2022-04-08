#ifndef GRAPHWINDOW_H
#define GRAPHWINDOW_H

#include "mainwindow.h"

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

class GraphWindow : public QWidget
{
    Q_OBJECT
private:
    QTableWidget *_ValueTab;
    QWidget * _ChartGuide;
    QWidget *_ChartWindow;
    QChart *_Chart;
    QToolBar *_UpperToolBar;
    QChartView *_ChartView;

    std::pair<int, int> getValueRange() const;

    void showChartWindow();

    void LineChart(QString ="Default Title");
    void LineToolBar();

    void BarChart();

    void BarToolBar();

    void PieToolBar();

    void PieChart();

public:
    GraphWindow(QTableWidget *, QWidget * = nullptr);
public slots:
    void BarChartCreator();
    void PieChartCreator();

    void LineChartCreator();

    void SaveAsPng();

    void ChartSelection();

    void explodeSlice();
};

#endif // GRAPHWINDOW_H
