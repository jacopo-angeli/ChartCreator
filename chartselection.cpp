#include "chartselection.h"
ChartSelection::ChartSelection(QWidget* parent): QWidget(parent){
    QVBoxLayout *MainLayout = new QVBoxLayout(this);

    QHBoxLayout *dataSelection = new QHBoxLayout;
    QLabel* dataRange=new  QLabel("Data Range");
    dataRange->setMaximumWidth((dataRange->fontMetrics().boundingRect(dataRange->text()).width())*1.2);
    QPushButton* pickBtn=new QPushButton("PICK");
    pickBtn->setMaximumWidth((pickBtn->fontMetrics().boundingRect(pickBtn->text()).width())*2.5);
    QLabel* selectedRange=new QLabel("Pick a range...");
    selectedRange->setStyleSheet("QLabel{border:1px solid darkgrey; background:white;}");
    dataSelection->addWidget(dataRange);
    dataSelection->addWidget(pickBtn);
    dataSelection->addWidget(selectedRange);


    MainLayout->addLayout(dataSelection);
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
    connect(BarC, SIGNAL(clicked()), parent->parent(), SLOT(openChartSettings()));


    QToolButton *CandleStickC = new QToolButton();
    CandleStickC->setText("CandleStick Chart");
    CandleStickC->setIcon(QIcon("../OOPPROJECT/icons/CandlestickChart.png"));
    CandleStickC->setMinimumWidth(150);
    CandleStickC->setMinimumHeight(150);
    CandleStickC->setIconSize(QSize(100,100));
    CandleStickC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);


    QToolButton *LineC = new QToolButton();
    LineC->setText("Line Charts");
    LineC->setIcon(QIcon("../OOPPROJECT/icons/LineChart.png"));
    LineC->setMinimumWidth(150);
    LineC->setMinimumHeight(150);
    LineC->setIconSize(QSize(100,100));
    LineC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //        connect(LineC, SIGNAL(clicked()), this, SLOT(LineChartCreator()));

    QToolButton *PieC = new QToolButton();
    PieC->setText("Pie Charts");
    PieC->setIcon(QIcon("../OOPPROJECT/icons/PieChart.png"));
    PieC->setMinimumWidth(150);
    PieC->setMinimumHeight(150);
    PieC->setIconSize(QSize(100,100));
    PieC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    //        connect(PieC, SIGNAL(clicked()), this, SLOT(PieChartCreator()));

    QToolButton *HistogramC = new QToolButton();
    HistogramC->setText("Histogram Charts");
    HistogramC->setIcon(QIcon("../OOPPROJECT/icons/HistogramChart.png"));
    HistogramC->setMinimumWidth(150);
    HistogramC->setMinimumHeight(150);
    HistogramC->setIconSize(QSize(100,100));
    HistogramC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    FrstRow->addStretch();
    FrstRow->addWidget(BarC);
    FrstRow->addWidget(CandleStickC);
    FrstRow->addWidget(LineC);
    FrstRow->addStretch();
    ScndRow->addStretch();
    ScndRow->addWidget(PieC, 0, Qt::AlignCenter);
    ScndRow->addWidget(HistogramC, 0, Qt::AlignCenter);
    ScndRow->addStretch();

    QPushButton *closeBtn = new QPushButton("Close",this);
    closeBtn->setMaximumWidth((closeBtn->fontMetrics().boundingRect(closeBtn->text()).width())*5);
    QPushButton *helpBtn = new QPushButton("?",this);
    helpBtn->setMaximumWidth((helpBtn->fontMetrics().boundingRect(helpBtn->text()).width())*5);

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addStretch();
    buttons->addWidget(helpBtn, 0, Qt::AlignRight);
    buttons->addWidget(closeBtn, 0, Qt::AlignRight);

    MainLayout->addLayout(buttons);
    setLayout(MainLayout);
    setFixedSize(QSize(500,450));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);
}

