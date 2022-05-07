#include "chartselection.h"
ChartSelection::ChartSelection(QWidget* parent): QWidget(parent){
    QVBoxLayout *MainLayout = new QVBoxLayout(this);
    MainLayout->addStretch();

    QHBoxLayout *FrstRow = new QHBoxLayout();
    QHBoxLayout *ScndRow = new QHBoxLayout();
    MainLayout->addLayout(FrstRow);
    MainLayout->addLayout(ScndRow);
    MainLayout->addStretch();

    QToolButton *BarC = new QToolButton();
    BarC->setText("Bar Chart");
    BarC->setIcon(QIcon("../OOPPROJECT/icons/BarChart.png"));
    BarC->setMinimumWidth(150);
    BarC->setMinimumHeight(150);
    BarC->setIconSize(QSize(100,100));
    BarC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(BarC, SIGNAL(clicked()), parent, SLOT(BarChartCreation()));


    QToolButton *CandleStickC = new QToolButton();
    CandleStickC->setText("CandleStick Chart");
    CandleStickC->setIcon(QIcon("../OOPPROJECT/icons/CandlestickChart.png"));
    CandleStickC->setMinimumWidth(150);
    CandleStickC->setMinimumHeight(150);
    CandleStickC->setIconSize(QSize(100,100));
    CandleStickC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(CandleStickC, SIGNAL(clicked()), parent, SLOT(CandleStickChartCreation()));


    QToolButton *LineC = new QToolButton();
    LineC->setText("Line Charts");
    LineC->setIcon(QIcon("../OOPPROJECT/icons/LineChart.png"));
    LineC->setMinimumWidth(150);
    LineC->setMinimumHeight(150);
    LineC->setIconSize(QSize(100,100));
    LineC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(LineC, SIGNAL(clicked()), parent, SLOT(LineChartCreation()));

    QToolButton *PieC = new QToolButton();
    PieC->setText("Pie Charts");
    PieC->setIcon(QIcon("../OOPPROJECT/icons/PieChart.png"));
    PieC->setMinimumWidth(150);
    PieC->setMinimumHeight(150);
    PieC->setIconSize(QSize(100,100));
    PieC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(PieC, SIGNAL(clicked()), parent, SLOT(PieChartCreation()));

    QToolButton *HistogramC = new QToolButton();
    HistogramC->setText("Histogram Charts");
    HistogramC->setIcon(QIcon("../OOPPROJECT/icons/HistogramChart.png"));
    HistogramC->setMinimumWidth(150);
    HistogramC->setMinimumHeight(150);
    HistogramC->setIconSize(QSize(100,100));
    HistogramC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(HistogramC, SIGNAL(clicked()), parent, SLOT(HistogramChartCreation()));

    FrstRow->addStretch();
    FrstRow->addWidget(BarC);
    FrstRow->addWidget(CandleStickC);
    FrstRow->addWidget(LineC);
    FrstRow->addStretch();
    ScndRow->addStretch();
    ScndRow->addWidget(PieC);
    ScndRow->addWidget(HistogramC);
    ScndRow->addStretch();

    setLayout(MainLayout);
}

