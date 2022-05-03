#ifndef CHARTSELECTION_H
#define CHARTSELECTION_H

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
class ChartSelection : public QWidget
{
    Q_OBJECT
public:
    ChartSelection(QWidget* = nullptr);
};

#endif // CHARTSELECTION_H
