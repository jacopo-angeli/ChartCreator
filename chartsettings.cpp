#include "chartsettings.h"
#include <QMainWindow>
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
ChartSettings::ChartSettings(Chart * chart,QWidget * parent) : QWidget(parent),  _Settings(new QGroupBox(this)), _ChartView(new QChartView(this)), _Chart(chart), _Title(new QLabel("Unset")), _Color(new QComboBox())
{

}


