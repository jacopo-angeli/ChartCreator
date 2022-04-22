#include "graphwindow.h"

GraphWindow::GraphWindow(QTableWidget *Table, QWidget *parent): QWidget(parent), _ValueTab(Table), _ChartGuide(new QWidget()), _ChartWindow(new QWidget()), _Chart(new QChart()), _UpperToolBar(new QToolBar()), _ChartView(new QChartView()){
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
    connect(BarC, SIGNAL(clicked()), this, SLOT(BarChartCreator()));


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
    connect(LineC, SIGNAL(clicked()), this, SLOT(LineChartCreator()));

    QToolButton *PieC = new QToolButton();
    PieC->setText("Pie Charts");
    PieC->setIcon(QIcon("../ProgettoPao_21_22/icons/PieChart.png"));
    PieC->setMinimumWidth(150);
    PieC->setMinimumHeight(150);
    PieC->setIconSize(QSize(100,100));
    PieC->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    connect(PieC, SIGNAL(clicked()), this, SLOT(PieChartCreator()));

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

void GraphWindow::BarChartCreator(){
    //clearing and rebuilding _Chart
    BarChart();
    //clearing and rebuilding _ToolBar
    BarToolBar();
    //clearing and rebuilding _ChartWindow
    showChartWindow();
}
void GraphWindow::LineChartCreator(){
    //clearing and rebuilding _Chart
    LineChart();
    //clearing and rebuilding _ToolBar
    LineToolBar();
    //clearing and rebuilding _ChartWindow
    showChartWindow();
}
void GraphWindow::PieChartCreator(){
    //clearing and rebuilding _Chart
    PieChart();
    //clearing and rebuilding _ToolBar
    PieToolBar();
    //clearing and rebuilding _ChartWindow
    showChartWindow();
}

void GraphWindow::BarChart(){
    if(_Chart) delete _Chart;
    _Chart=new QChart();

    QList<QBarSet*>BarsSets;

    _ValueTab->selectColumn(0);
    QList<QTableWidgetItem*> FirstColumnElements = _ValueTab->selectedItems();
    _ValueTab->clearSelection();

    for(int i=1; i<FirstColumnElements.length(); i++){
        if(FirstColumnElements[i]->text().toStdString() != "") {
            BarsSets.append(new QBarSet(FirstColumnElements[i]->text()));
        }else break;
    }

    //categories
    QStringList categories;
    _ValueTab->selectRow(0);
    QList<QTableWidgetItem*> FirstRowElements = _ValueTab->selectedItems();
    _ValueTab->clearSelection();
    for(int i=1; i<FirstRowElements.length(); i++){
        if(FirstRowElements[i]->text().toStdString() != ""){
            categories << FirstRowElements[i]->text();
        }
    }

    //BarSetsPopulation
    for(int i=0; i<BarsSets.length(); i++){
        //prendere colonna per colonna e tirarmi giù i valori corrispondenti al'indice i+1
        for(int j=1; j<=categories.length(); j++){
            //devo inserire sul barsets i i valori dell'elemento i della colonna j
            *(BarsSets[i]) << _ValueTab->item(i+1, j)->text().toInt();
        }
    }
    QBarSeries *Series = new QBarSeries();
    for(int i=0; i<BarsSets.length();i++){
        Series->append(BarsSets[i]);
    }

    _Chart->addSeries(Series);

    //x axis
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    _Chart->addAxis(axisX, Qt::AlignBottom);
    Series->attachAxis(axisX);

    //y axis
    QValueAxis *axisY = new QValueAxis();
    std::pair<int, int> VRange = getValueRange();
    axisY->setRange(0, VRange.second*2);
    _Chart->addAxis(axisY, Qt::AlignLeft);
    Series->attachAxis(axisY);

    //legend
    _Chart->legend()->setVisible(true);
    _Chart->legend()->setAlignment(Qt::AlignBottom);
}
void GraphWindow::BarToolBar(){
    if(_UpperToolBar) delete _UpperToolBar;
    _UpperToolBar = new QToolBar();

    QToolButton *SaveBtn = new QToolButton;
    SaveBtn->setText("Save");
    SaveBtn->setIcon(QIcon("../ProgettoPao_21_22/icons/Save.png"));
    connect(SaveBtn, SIGNAL(clicked()), this, SLOT(OpenColorSettings()));
    SaveBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SaveBtn->setMinimumWidth(100);
    SaveBtn->setMinimumHeight(100);

    QToolButton *ColorSettings = new QToolButton;
    ColorSettings->setText("Change Color");
    ColorSettings->setIcon(QIcon("../ProgettoPao_21_22/icons/ColorSettings.png"));
    connect(ColorSettings, SIGNAL(clicked()), this, SLOT(OpenColorSettings()));
    ColorSettings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ColorSettings->setMinimumWidth(100);
    ColorSettings->setMinimumHeight(100);

    QToolButton *ChangeChart = new QToolButton;
    ChangeChart->setText("Change Chart Type");
    ChangeChart->setIcon(QIcon("../ProgettoPao_21_22/icons/Back.png"));
    connect(ChangeChart, SIGNAL(clicked()), this, SLOT(ChartSelection()));
    ChangeChart->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ChangeChart->setMinimumWidth(100);
    ChangeChart->setMinimumHeight(100);

    _UpperToolBar->setIconSize(QSize(50,50));
    _UpperToolBar->addWidget(SaveBtn);
    _UpperToolBar->addSeparator();
    _UpperToolBar->addWidget(ColorSettings);
    _UpperToolBar->addSeparator();
    _UpperToolBar->addWidget(ChangeChart);
    _UpperToolBar->setStyleSheet("QToolBar{background-color:rgb(160,160,160); border-radius:10%; padding:5px;} QToolButton{font-size:11pt; border: 1.5px solid transparent;} QToolButton:hover{border:1.5px solid black; border-radius: 10%;}");
}

void GraphWindow::LineChart(QString title){
    if(_Chart) delete _Chart;
    _Chart=new QChart();
    _ValueTab->selectColumn(0);
    QList<QTableWidgetItem*> FirstColumnItems = _ValueTab->selectedItems();
    _ValueTab->clearSelection();
    QLineSeries *series = new QLineSeries();

    //If first column is a dates column
    QRegExp reDate("^(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\\d\\d$");
    if(reDate.exactMatch(_ValueTab->item(1,0)->text())){

        for(int i=1; i<FirstColumnItems.length(); i++){
            QString dateCell = _ValueTab->item(i, 0)->text();
            QStringList values = dateCell.split(QLatin1Char('/'));
            QDateTime date;
            date.setDate(QDate(values[2].toInt(), values[1].toInt(), values[0].toInt()));
            series->append(date.toMSecsSinceEpoch(), _ValueTab->item(i, 1)->text().toInt());
        }
        _Chart->addSeries(series);
        QDateTimeAxis *XAxis = new QDateTimeAxis();
        //            XAxis->setTickCount(FirstColumnItems.length()-1);
        XAxis->setFormat("dd MMM yyyy");
        XAxis->setTitleText(FirstColumnItems[0]->text());
        _Chart->addAxis(XAxis, Qt::AlignBottom);
        series->attachAxis(XAxis);

        QValueAxis *YAxis = new QValueAxis();
        YAxis->setLabelFormat("%i");
        YAxis->setTitleText(_ValueTab->item(0, 1)->text());
        _Chart->addAxis(YAxis, Qt::AlignLeft);
        series->attachAxis(YAxis);

    }else{
        for(int i=1; i<FirstColumnItems.length(); i++){
            series->append(_ValueTab->item(i, 0)->text().toInt(), _ValueTab->item(i, 1)->text().toInt());
        }
        _Chart->addSeries(series);
        _Chart->createDefaultAxes();
    }

    _Chart->legend()->setVisible(true);
    _Chart->legend()->setAlignment(Qt::AlignBottom);

    _Chart->setTitle(title);
    _Chart->setAnimationOptions(QChart::SeriesAnimations);
}
void GraphWindow::LineToolBar(){
    if(_UpperToolBar) delete _UpperToolBar;
    _UpperToolBar = new QToolBar();

    QToolButton *SaveBtn = new QToolButton();
    SaveBtn->setText("Save");
    SaveBtn->setIcon(QIcon("../ProgettoPao_21_22/icons/Save.png"));
    connect(SaveBtn, SIGNAL(clicked()), this, SLOT(OpenColorSettings()));
    SaveBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SaveBtn->setMinimumWidth(100);
    SaveBtn->setMinimumHeight(100);

    QToolButton *ColorSettings = new QToolButton();
    ColorSettings->setText("Change Color");
    ColorSettings->setIcon(QIcon("../ProgettoPao_21_22/icons/ColorSettings.png"));
    connect(ColorSettings, SIGNAL(clicked()), this, SLOT(OpenColorSettings()));
    ColorSettings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ColorSettings->setMinimumWidth(100);
    ColorSettings->setMinimumHeight(100);

    QSpinBox *TickCounter = new QSpinBox();
    TickCounter->setValue(5);
    TickCounter->setMinimumWidth(100);

    _UpperToolBar->setIconSize(QSize(50,50));
    _UpperToolBar->addWidget(SaveBtn);
    _UpperToolBar->addSeparator();
    _UpperToolBar->addWidget(ColorSettings);
    _UpperToolBar->addSeparator();
    _UpperToolBar->addWidget(TickCounter);
    _UpperToolBar->setStyleSheet("QToolBar{background-color:rgb(255,255,255); border-radius:10%; padding:5px;} QToolButton{font-size:11pt; border: 1.5px solid transparent;} QToolButton:hover{border:1.5px solid black; border-radius: 10%;}");
}

void GraphWindow::PieToolBar(){
    if(_UpperToolBar)delete _UpperToolBar;
    _UpperToolBar = new QToolBar();
    QToolButton *SaveBtn = new QToolButton;
    SaveBtn->setText("Save as PNG");
    SaveBtn->setIcon(QIcon("../ProgettoPao_21_22/icons/Save.png"));
    connect(SaveBtn, SIGNAL(clicked()), this, SLOT(SaveAsPng()));
    SaveBtn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    SaveBtn->setMinimumWidth(100);
    SaveBtn->setMinimumHeight(100);

    QToolButton *ColorSettings = new QToolButton;
    ColorSettings->setText("Change Color");
    ColorSettings->setIcon(QIcon("../ProgettoPao_21_22/icons/ColorSettings.png"));
    connect(ColorSettings, SIGNAL(clicked()), this, SLOT(SaveAsPng()));
    ColorSettings->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    ColorSettings->setMinimumWidth(100);
    ColorSettings->setMinimumHeight(100);

    QList<QtCharts::QAbstractSeries*> series = _Chart->series();
    QPieSeries *PieSeries = static_cast<QPieSeries*>(series[0]);
    QList<QtCharts::QPieSlice*> slices = PieSeries->slices();
    for (int i=0; i<slices.length() ; i++) {
        connect(slices[i], SIGNAL(clicked()), this, SLOT(explodeSlice()));
        QFont f = slices[i]->labelFont();
        f.setPointSize(11);
        slices[i]->setLabelFont(f);
        slices[i]->setBorderWidth(1);
        slices[i]->setBorderColor(QColor("black"));
    }

    _UpperToolBar->setIconSize(QSize(50,50));
    _UpperToolBar->addWidget(SaveBtn);
    _UpperToolBar->addSeparator();
    _UpperToolBar->addWidget(ColorSettings);
    _UpperToolBar->setStyleSheet("QToolBar{background-color:rgb(255,255,255); border-radius:10%; padding:5px;} QToolButton{font-size:11pt; border: 1.5px solid transparent;}QToolButton::item:hover{background-color:blue;} QToolButton:hover{border:1.5px solid black; border-radius: 10%; background-color:lightblue; border-color:blue;} QWidgetAction{backgroundcolor:blue;}");
}
void GraphWindow::PieChart(){
    if(_Chart)delete _Chart;
    _Chart = new QChart();
    _ValueTab->selectRow(0);
    QList<QTableWidgetItem*> FirstRowItems = _ValueTab->selectedItems();
    _ValueTab->clearSelection();

    if(FirstRowItems[0]->text().toStdString() != ""){
        QPieSeries *series = new QPieSeries();
        for(int i=0; i<FirstRowItems.length(); i++){
            if(FirstRowItems[i]->text().toStdString() != ""){
                series->append(FirstRowItems[i]->text(), _ValueTab->item(1,i)->text().toInt());
            }else break;
        }

        _Chart->addSeries(series);

        _Chart->legend()->setVisible(true);
        QFont f = _Chart->legend()->font();
        f.setPointSize(15);
        _Chart->legend()->setFont(f);
        _Chart->legend()->setAlignment(Qt::AlignBottom);

        _Chart->setTitle("Chart Title");
        _Chart->setAnimationOptions(QChart::SeriesAnimations);
    }
}
void GraphWindow::explodeSlice(){
    if(dynamic_cast<QPieSlice*>(QObject::sender())){
        QPieSlice* slice = static_cast<QPieSlice*>(QObject::sender());
        if(slice->isExploded()){
            slice->setExploded(false);
            slice->setBorderWidth(1);
            slice->setLabelVisible(false);
        }else{
            slice->setExploded();
            slice->setBorderWidth(2);
            slice->setLabelVisible();
        }
    }
}

void GraphWindow::SaveAsPng(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Chart"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),tr("Images (*.png)"));
    if(!(fileName.contains(".png"))) fileName.append(".png");
    _ChartView->grab().save(fileName);
}
std::pair<int, int> GraphWindow::getValueRange() const{
    int min=INT_MAX, max=INT_MIN;
    int ColumnCount=0;
    _ValueTab->selectRow(0);
    QList<QTableWidgetItem*> headerItem = _ValueTab->selectedItems();
    _ValueTab->clearSelection();
    while(headerItem[ColumnCount]->text().toStdString() != ""){
        ColumnCount++;
    }
    for(int i=1; i<ColumnCount; i++){
        _ValueTab->selectColumn(i);
        QList<QTableWidgetItem*> ColumnElements = _ValueTab->selectedItems();
        _ValueTab->clearSelection();
        for (int j=1; j<ColumnElements.length(); j++){
            int tempval = ColumnElements[j]->text().toInt();
            min = (tempval < min ) ? tempval : min;
            max = (tempval > max ) ? tempval : max;
        }
    }
    return std::make_pair(min, max);
}

void GraphWindow::ChartSelection(){
    _ChartWindow->close();
    this->show();
}

void GraphWindow::showChartWindow(){
    if(_ChartWindow->layout()) delete _ChartWindow->layout();
    if(_ChartView) delete _ChartView;

    QVBoxLayout *MainLayout = new QVBoxLayout(_ChartWindow);

    _ChartView=new QChartView(_ChartWindow);
    _ChartView->setChart(_Chart);
    _ChartView->setRenderHint(QPainter::Antialiasing);

    MainLayout->setMenuBar(_UpperToolBar);
    MainLayout->addWidget(_ChartView);

    _ChartWindow->setLayout(MainLayout);
    _ChartWindow->setStyleSheet("background-color:white;");
    _ChartWindow->resize(1024, 920);

    close();

    _ChartWindow->show();
}

