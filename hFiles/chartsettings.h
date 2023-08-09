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
    //Creare PairToTag
    QPair<QPair<int, int>, QPair<int, int>> tagToPairPair(const QString&) const;
    QPair<int, int> tagToPair(const QString&) const;
private:
    QLabel *_Title;
    QComboBox * _Color;
public:
    ChartSettings(QWidget* = nullptr);
    virtual ~ChartSettings();
    Chart* getChart() const;

    void setTitlePosition(QPair<int, int> = QPair<int, int>(0,0));
    QPair<int, int> getTitlePosition() const;

    void setColorIndex(int);

    virtual void refresh(QTableWidget*) const;
    virtual void setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>> = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(0,0), QPair<int, int>(0,0))) =0;
    virtual QPair<QPair<int, int>, QPair<int, int>> getCategoriesRange() const =0;
    virtual QJsonObject toJSON() const;
    virtual void fromJSON(const QJsonObject&);
};

#endif // CHARTSETTINGS_H
