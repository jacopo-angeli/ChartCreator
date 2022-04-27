#include "chartselection.h"



    ChartSelection::ChartSelection(QWidget* parent): QWidget(parent){
        QVBoxLayout *MainLayout = new QVBoxLayout(this);
        QHBoxLayout *FrstRow = new QHBoxLayout();
        QHBoxLayout *ScndRow = new QHBoxLayout();
        MainLayout->addLayout(FrstRow);
        MainLayout->addLayout(ScndRow);

        QToolButton *BarC = new QToolButton();
        BarC->setText("Bar Chart");
        BarC->setIcon(QIcon("../ProgettoPao_21_22/icons/BarChart.png"));
        BarC->setMinimumWidth(150);
        BarC->setMinimumHeight(150);
        BarC->setIconSize(QSize(100,100));
        BarC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//        connect(BarC, SIGNAL(clicked()), this, SLOT(BarChartCreator()));


        QToolButton *CandleStickC = new QToolButton();
        CandleStickC->setText("CandleStick Chart");
        CandleStickC->setIcon(QIcon("../ProgettoPao_21_22/icons/CandlestickChart.png"));
        CandleStickC->setMinimumWidth(150);
        CandleStickC->setMinimumHeight(150);
        CandleStickC->setIconSize(QSize(100,100));
        CandleStickC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


        QToolButton *LineC = new QToolButton();
        LineC->setText("Line Charts");
        LineC->setIcon(QIcon("../ProgettoPao_21_22/icons/LineChart.png"));
        LineC->setMinimumWidth(150);
        LineC->setMinimumHeight(150);
        LineC->setIconSize(QSize(100,100));
        LineC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//        connect(LineC, SIGNAL(clicked()), this, SLOT(LineChartCreator()));

        QToolButton *PieC = new QToolButton();
        PieC->setText("Pie Charts");
        PieC->setIcon(QIcon("../ProgettoPao_21_22/icons/PieChart.png"));
        PieC->setMinimumWidth(150);
        PieC->setMinimumHeight(150);
        PieC->setIconSize(QSize(100,100));
        PieC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
//        connect(PieC, SIGNAL(clicked()), this, SLOT(PieChartCreator()));

        QToolButton *HistogramC = new QToolButton();
        HistogramC->setText("Histogram Charts");
        HistogramC->setIcon(QIcon("../ProgettoPao_21_22/icons/HistogramChart.png"));
        HistogramC->setMinimumWidth(150);
        HistogramC->setMinimumHeight(150);
        HistogramC->setIconSize(QSize(100,100));
        HistogramC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        FrstRow->addWidget(BarC);
        FrstRow->addWidget(CandleStickC);
        FrstRow->addWidget(LineC);
        ScndRow->addWidget(PieC);
        ScndRow->addWidget(HistogramC);

        setLayout(MainLayout);
        setWindowFlags(Qt::WindowStaysOnTopHint);
    }

