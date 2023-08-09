#include "../hFiles/controller.h"
#include "../hFiles/candlestick.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include<string>
#include "../hFiles/area.h"
Controller::Controller():guideWindow(new QWidget()), _MainWindow(new MainWindow(this)),  _ActiveFiles(QMap<QString, QString>()){
    lastSessionRestore();

    QFile file(":/files/Guida.html");

    guideWindow->setMinimumSize(500,500);
    guideWindow->setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
    QVBoxLayout * l = new QVBoxLayout();

    if(file.open(QIODevice::ReadOnly)){
       QString data = file.readAll();
       file.close();

       QTextBrowser *tb = new QTextBrowser(this);

       tb->setHtml(data);
       l->addWidget(tb);
       tb->setOpenExternalLinks(true);

       guideWindow->setLayout(l);
    }

    QHBoxLayout* btns= new QHBoxLayout();
    QPushButton* closeBtn = new QPushButton("Close");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(toggleGuideWindow()));

    btns->addStretch();
    btns->addWidget(closeBtn);

    l->addLayout(btns);

    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->setAnimated(true);
    _MainWindow->show();
}
Controller::~Controller(){
    delete guideWindow;
    delete _MainWindow;
}
bool Controller::fileSave(int tableIndex, QString fileName) const{
    QString filePath = "";
    if(fileName==""){
        filePath = QFileDialog::getSaveFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
        if(filePath == "") return false;
        if(!(filePath.contains(".crt"))) filePath.append(".crt");
        _MainWindow->setCurrentTabTitle(QString("../"+(filePath.split("/")).last()));
    }else filePath=_ActiveFiles[fileName];

    //TODO: File name change while modifing it problem
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream stream(&file);
        QJsonObject fullfile;
        QTableWidget* table = _MainWindow->getFullTable(tableIndex);

        QJsonObject tableJSON;

        table->selectAll();
        QList<QTableWidgetItem*> ItemList = table->selectedItems();
        table->clearSelection();

        int i=0;
        for(auto it = ItemList.begin(); it != ItemList.end(); it++){
            QJsonObject cell;
            cell["row"] = (*it)->row();
            cell["column"] = (*it)->column();
            cell["value"] = (*it)->text();
            QFont f = (*it)->font();
            cell["fontSize"] = f.pointSize();
            tableJSON[QString::number(i)] = cell;
            i++;
        }
        fullfile["table"] = tableJSON;

        int chartNumber = _MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1;
        QJsonObject charts;
        charts["chartNumber"] = chartNumber;
        for(auto i = 0; i<chartNumber; i++){
            ChartSettings* chartTab = _MainWindow->getChartTab(i, tableIndex);
            charts[QString::number(i)] = chartTab->toJSON();
        }

        fullfile["charts"] = charts;
        stream<<QJsonDocument(fullfile).toJson();
        file.close();
    }else{
//        std::cout << "Cannot Open file : "<<filePath;
    }
    return true;
}
void Controller::UpperInsert(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentRow=currentTable->currentRow()+1;
    currentTable->insertRow(currentRow-1);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.first>=currentRow){
            //Aumento di una riga il titlePosition
            QPair<int, int> newPos = QPair<int, int>(pos.first+1, pos.second);
            currentTab->setTitlePosition(newPos);
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.first>=currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getOpeningPricesRange();
            if(range.first.first>=currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getClosingPricesRange();
            if(range.first.first>=currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getHighestPricesRange();
            if(range.first.first>=currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getLowestPricesRange();
            if(range.first.first>=currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.first>=currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
                else if(range.second.first>=currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            }
            range = areaLinePieTab->getDataRange();
            if(range.first.first>=currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = areaLinePieTab->getLabelsRange();
            if(range.first.first>=currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>=currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
        }
    }
}
void Controller::LowerInsert(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentRow=currentTable->currentRow()+1;
    currentTable->insertRow(currentRow);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.first>currentRow){
            //Aumento di una riga il titlePosition
            QPair<int, int> newPos = QPair<int, int>(pos.first+1, pos.second);
            currentTab->setTitlePosition(newPos);
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.first>currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getOpeningPricesRange();
            if(range.first.first>currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getClosingPricesRange();
            if(range.first.first>currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getHighestPricesRange();
            if(range.first.first>currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = candleStickTab->getLowestPricesRange();
            if(range.first.first>currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.first>currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
                else if(range.second.first>currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            }
            range = areaLinePieTab->getDataRange();
            if(range.first.first>currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            range = areaLinePieTab->getLabelsRange();
            if(range.first.first>currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first+1, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
            else if(range.second.first>currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first+1, range.second.second)));
        }
    }
}
void Controller::LeftInsert(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentColumn=currentTable->currentColumn()+1;
    currentTable->insertColumn(currentColumn-1);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.second>=currentColumn){
            //Aumento di una riga il titlePosition
            QPair<int, int> newPos = QPair<int, int>(pos.first, pos.second+1);
            currentTab->setTitlePosition(newPos);
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.second>=currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getOpeningPricesRange();
            if(range.first.second>=currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getClosingPricesRange();
            if(range.first.second>=currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getHighestPricesRange();
            if(range.first.second>=currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getLowestPricesRange();
            if(range.first.second>=currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.second>=currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
                else if(range.second.second>=currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            }
            range = areaLinePieTab->getDataRange();
            if(range.first.second>=currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = areaLinePieTab->getLabelsRange();
            if(range.first.second>=currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>=currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
        }
    }
}
void Controller::RightInsert(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentColumn=currentTable->currentColumn()+1;
    currentTable->insertColumn(currentColumn);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.second>currentColumn){
            //Aumento di una riga il titlePosition
            QPair<int, int> newPos = QPair<int, int>(pos.first, pos.second+1);
            currentTab->setTitlePosition(newPos);
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.second>currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getOpeningPricesRange();
            if(range.first.second>currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getClosingPricesRange();
            if(range.first.second>currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getHighestPricesRange();
            if(range.first.second>currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = candleStickTab->getLowestPricesRange();
            if(range.first.second>currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.second>currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
                else if(range.second.second>currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            }
            range = areaLinePieTab->getDataRange();
            if(range.first.second>currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
            range = areaLinePieTab->getLabelsRange();
            if(range.first.second>currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second+1),QPair<int, int>(range.second.first, range.second.second+1)));
            else if(range.second.second>currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second+1)));
        }
    }
}
void Controller::TableReset(){
    QMessageBox::StandardButton Reply;
    Reply = QMessageBox::question(_MainWindow, "WARNING", "You are cleaning the entire table. Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if(Reply == QMessageBox::Yes){
        _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex())->clear();
    }
}
void Controller::RowReset(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentIndex = currentTable->currentRow();
    for(int i=0; i<currentTable->columnCount(); i++)
       if(currentTable->item(currentIndex, i))
           currentTable->item(currentIndex, i)->setText("");
}
void Controller::ColumnReset(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentIndex = currentTable->currentColumn();
    for(int i=0; i<currentTable->rowCount(); i++)
        if(currentTable->item(i, currentIndex))
            currentTable->item(i, currentIndex)->setText("");
}
void Controller::SelectionReset(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++)
        if(*it)
            (*it)->setText("");
}
void Controller::RowDelete(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentRow=currentTable->currentRow()+1;
    for(int i=0; i< currentTable->columnCount(); i++)
        if(currentTable->item(currentRow-1, i))
            currentTable->item(currentRow-1, i)->setText("");
    currentTable->removeRow(currentRow-1);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.first==currentRow){
            currentTab->setTitlePosition();
        }else if(pos.first>currentRow){
            currentTab->setTitlePosition(QPair<int, int>(pos.first-1, pos.second));
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    candleStickTab->setCategoriesRange();
                else
                    candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));

            range = candleStickTab->getOpeningPricesRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    candleStickTab->setOpeningPricesRange();
                else
                    candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));

            range = candleStickTab->getClosingPricesRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    candleStickTab->setClosingPricesRange();
                else
                    candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));

            range = candleStickTab->getHighestPricesRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    candleStickTab->setHighestPricesRange();
                else
                    candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));

            range = candleStickTab->getLowestPricesRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    candleStickTab->setLowestPricesRange();
                else
                    candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.first==currentRow){
                    if(range.first.first==range.second.first)
                        barChart->setCategoriesRange();
                    else
                        barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
                }
                else if(range.first.first>currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
                else if(range.second.first>currentRow)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            range = areaLinePieTab->getDataRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    areaLinePieTab->setDataRange();
                else
                    areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));

            range = areaLinePieTab->getLabelsRange();
            if(range.first.first==currentRow){
                if(range.first.first==range.second.first)
                    areaLinePieTab->setLabelsRange();
                else
                    areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            }
            else if(range.first.first>currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first-1, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
            else if(range.second.first>currentRow)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first-1, range.second.second)));
        }
    }
}
void Controller::ColumnDelete(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    int currentColumn=currentTable->currentColumn()+1;
    for(int i=0; i< currentTable->rowCount(); i++)
        if(currentTable->item(i, currentColumn-1))
            currentTable->item(i, currentColumn-1)->setText("");
    currentTable->removeColumn(currentColumn-1);
    //Aumentare di una riga tutti i range da currentRow in poi
    //Scorro tutti i chart, prendo tutti i range e controllo se first.first è maggiore di currentRow
    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        QPair<int, int> pos = currentTab->getTitlePosition();
        if(pos.second==currentColumn){
            currentTab->setTitlePosition();
        }else if(pos.second>currentColumn){
            currentTab->setTitlePosition(QPair<int, int>(pos.first, pos.second-1));
        }
        QPair<QPair<int, int>, QPair<int, int>> range = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(), QPair<int, int>());
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            range = candleStickTab->getCategoriesRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    candleStickTab->setCategoriesRange();
                else
                    candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));

            range = candleStickTab->getOpeningPricesRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    candleStickTab->setOpeningPricesRange();
                else
                    candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setOpeningPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));

            range = candleStickTab->getClosingPricesRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    candleStickTab->setClosingPricesRange();
                else
                    candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setClosingPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));

            range = candleStickTab->getHighestPricesRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    candleStickTab->setHighestPricesRange();
                else
                    candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setHighestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));

            range = candleStickTab->getLowestPricesRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    candleStickTab->setLowestPricesRange();
                else
                    candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                candleStickTab->setLowestPricesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab)){
                range = barChart->getCategoriesRange();
                if(range.first.second==currentColumn){
                    if(range.first.second==range.second.second)
                        barChart->setCategoriesRange();
                    else
                        barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
                }
                else if(range.first.second>currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
                else if(range.second.second>currentColumn)
                    barChart->setCategoriesRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }

            range = areaLinePieTab->getDataRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    areaLinePieTab->setDataRange();
                else
                    areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                areaLinePieTab->setDataRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));

            range = areaLinePieTab->getLabelsRange();
            if(range.first.second==currentColumn){
                if(range.first.second==range.second.second)
                    areaLinePieTab->setLabelsRange();
                else
                    areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
            }
            else if(range.first.second>currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second-1),QPair<int, int>(range.second.first, range.second.second-1)));
            else if(range.second.second>currentColumn)
                areaLinePieTab->setLabelsRange(QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>(range.first.first, range.first.second),QPair<int, int>(range.second.first, range.second.second-1)));
        }
    }
}
void Controller::LeftAlign(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
        (*it)->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    }
}
void Controller::CenterAlign(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
        (*it)->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    }
}
void Controller::RightAlign(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
        (*it)->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    }
}
void Controller::SpinBox(){
    _MainWindow->setSpinBox(10);
}
void Controller::SetTextSize(){
    QTableWidget* currentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QFont TFont= currentTable->font();
    TFont.setPointSize(_MainWindow->getSpinValue());
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++)
        (*it)->setFont(TFont);
}
void Controller::TabClose(int index){
    QString tabName = _MainWindow->getTabName(index);
    QMessageBox::StandardButton Reply;
    Reply = QMessageBox::question(_MainWindow, "Unsaved File", tabName+" may have usaved changes. Would you like to save them?", QMessageBox::Cancel|QMessageBox::Discard|QMessageBox::Save);
    if(Reply == QMessageBox::Save){
        if(fileSave(index, tabName=="Untitled" ? "" : tabName)){
            _MainWindow->closeTab(index);
            if(tabName != "Untitled") _ActiveFiles.remove(tabName);
        }
    }else if(Reply == QMessageBox::Discard){
        _MainWindow->closeTab(index);
        if(tabName != "Untitled") _ActiveFiles.remove(tabName);
    }
}
void Controller::ChartTabClose(int index){
    if(index != _MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1){
        _MainWindow->closeChartTab(index);
    }
}
void Controller::lastSessionRestore(){
    if(QDir(QDir::homePath() + "/.chartCreator").exists()){
        QFile file(QDir::homePath() + "/.chartCreator"+"/cnfg.json");
        if (file.open(QIODevice::ReadOnly)){
            QByteArray data = file.readAll();
            file.close();
            QJsonDocument doc = QJsonDocument::fromJson(data);
            QJsonObject lastArrayState = doc.object();
            for(int i=0; i<lastArrayState.size()-1; i++){
                QJsonObject keyValuePair = lastArrayState.value(QString("File ")+QString::number(i)).toObject();
                fileOpen(keyValuePair.value("path").toString());
            }
        }
    }
}
void Controller::openFile(){
    fileOpen();
}
void Controller::saveACopy(){
    fileSave(_MainWindow->getCurrentTabIndex());
}
void Controller::newTab(){
    _MainWindow->newTab();
}
void Controller::saveFile(){
    fileSave(_MainWindow->getCurrentTabIndex(), _MainWindow->getTabName()=="Untitled" ? "" : _MainWindow->getTabName());
}
void Controller::mainWindowCloseEvent(){
    if(!QDir(QDir::homePath() + "/.chartCreator").exists()) QDir(QDir::homePath() + "/.chartCreator").mkpath(".");
    QFile file(QDir::homePath() + "/.chartCreator" + "/cnfg.json");
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream stream(&file);
        QJsonObject obj;
        obj.insert("File number", _ActiveFiles.size());
        int i=0;
        for (auto it = _ActiveFiles.begin(); it!=_ActiveFiles.end() ; it++) {
            QJsonObject file;
            file.insert("path", it.value());
            obj.insert(QString("File ")+QString::number(i), file);
            i++;
        }
        stream<<QJsonDocument(obj).toJson();
        file.close();
    }else{
//        std::cout<<"file cannot be opened";
    }
    _MainWindow->close();
};
void Controller::BarChartCreation(){
    _MainWindow->chartTypeSelected(Flags::BARS);
}
void Controller::CandleStickChartCreation(){
    _MainWindow->chartTypeSelected(Flags::CANDLESTICK);
}
void Controller::LineChartCreation(){
    _MainWindow->chartTypeSelected(Flags::LINES);
}
void Controller::PieChartCreation(){
    _MainWindow->chartTypeSelected(Flags::PIE);
}
void Controller::AreaChartCreation(){
    _MainWindow->chartTypeSelected(Flags::AREA);
}
void Controller::pickTitle(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta la posizione della prima cella della selezione con la tag contenente l'attuale posizione del titolo
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e il titolo con il titolo di default
                //Se le posizioni sono diverse
                    //Aggiorna la tag con l'attuale posizione della prima cella della selezione
                    //Aggiorna il titolo del grafico con il contenuto della prima cella della selezione
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    if(selections.size() == 0){
        _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->setTitlePosition();
        _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTitle("");
    }else{
        QPair<int, int> newPosition = QPair<int, int>((selections.first().row()+1),(selections.first().column()+1));
        QTableWidgetItem* cellSelected = CurrentTable->item(newPosition.first-1, newPosition.second-1);
        if(newPosition != _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getTitlePosition()){
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->setTitlePosition(newPosition);
            if(cellSelected)
                _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTitle(cellSelected->text());
        }else{
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->setTitlePosition();
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTitle("");
        }
    }
}
void Controller::pickOpeningPrices(){
    //Controllare se è il caso di effetuare modifiche
    //Effettuarle sul modello
    //Aggiornare la vista
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    CandleStickSettings* currentChartTab = static_cast<CandleStickSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setOpeningPricesRange();
        static_cast<CandleStick*>(currentChartTab->getChart())->clearOpeningPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getOpeningPricesRange()){
            currentChartTab->setOpeningPricesRange(newPositions);
            static_cast<CandleStick*>(currentChartTab->getChart())->setOpeningPrices(CurrentTable, selections);
        }else{
            currentChartTab->setOpeningPricesRange();
            static_cast<CandleStick*>(currentChartTab->getChart())->clearOpeningPrices();
        }
    }
}
void Controller::pickClosingPrices(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    CandleStickSettings* currentChartTab = static_cast<CandleStickSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setClosingPricesRange();
        static_cast<CandleStick*>(currentChartTab->getChart())->clearClosingPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getClosingPricesRange()){
            currentChartTab->setClosingPricesRange(newPositions);
            static_cast<CandleStick*>(currentChartTab->getChart())->setClosingPrices(CurrentTable, selections);
        }else{
            currentChartTab->setClosingPricesRange();
            static_cast<CandleStick*>(currentChartTab->getChart())->clearClosingPrices();
        }
    }
}
void Controller::pickLowestPrices(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    CandleStickSettings* currentChartTab = static_cast<CandleStickSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setLowestPricesRange();
        static_cast<CandleStick*>(currentChartTab->getChart())->clearLowestPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getLowestPricesRange()){
            currentChartTab->setLowestPricesRange(newPositions);
            static_cast<CandleStick*>(currentChartTab->getChart())->setLowestPrices(CurrentTable, selections);
        }else{
            currentChartTab->setLowestPricesRange();
            static_cast<CandleStick*>(currentChartTab->getChart())->clearLowestPrices();
        }
    }
}
void Controller::pickHighestPrices(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    CandleStickSettings* currentChartTab = static_cast<CandleStickSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setHighestPricesRange();
        static_cast<CandleStick*>(currentChartTab->getChart())->clearHighestPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getHighestPricesRange()){
            currentChartTab->setHighestPricesRange(newPositions);
            static_cast<CandleStick*>(currentChartTab->getChart())->setHighestPrices(CurrentTable, selections);
        }else{
            currentChartTab->setHighestPricesRange();
            static_cast<CandleStick*>(currentChartTab->getChart())->clearHighestPrices();
        }
    }
}
void Controller::pickDataRange(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    AreaLinePieSettings* currentChartTab = static_cast<AreaLinePieSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setDataRange();
        currentChartTab->getChart()->clearData();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getDataRange()){
            currentChartTab->setDataRange(newPositions);
            currentChartTab->getChart()->setSeries(CurrentTable, selections, currentChartTab->getParseMethod());
        }else{
            currentChartTab->setDataRange();
            currentChartTab->getChart()->clearData();
        }
    }
}
void Controller::pickLabels(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    AreaLinePieSettings* currentChartTab = static_cast<AreaLinePieSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    if(selections.size() == 0){
        currentChartTab->setLabelsRange();
        currentChartTab->getChart()->clearLabels();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getLabelsRange()){
            currentChartTab->setLabelsRange(newPositions);
            currentChartTab->getChart()->setLabels(CurrentTable, selections);
        }else{
            currentChartTab->setLabelsRange();
            currentChartTab->getChart()->clearLabels();
        }
    }
}
void Controller::pickCategories(){
    //Controlla la corrente porzione di tabella selezionata
        //Se la selezione è vuota
            //Sostituisce la tag con "Unset" e il titolo con il titolo di default
        //Se la selezione non è vuota
            //Confronta le posizioni della selezione con la tag contenente le attuali posizioni
                //Se le posizioni sono uguali
                    //Sostituisce la tag con "Unset" e modifica il grafico
                //Se le posizioni sono diverse
                    //Aggiorna la tag con le nuove posizioni
                    //Aggiorna il grafico
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList selections = CurrentTable->selectionModel()->selectedIndexes();
    ChartSettings* currentChartTab =_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex());
    if(selections.size() == 0){
        currentChartTab->setCategoriesRange();
        if(CandleStick* candleStickChart = dynamic_cast<CandleStick*>(currentChartTab->getChart()))
            candleStickChart->clearCategories();
        else
            static_cast<Bar*>(currentChartTab->getChart())->clearCategories();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getCategoriesRange()){
            currentChartTab->setCategoriesRange(newPositions);
            if(CandleStick* candleStickChart = dynamic_cast<CandleStick*>(currentChartTab->getChart()))
                candleStickChart->setCategories(CurrentTable, selections);
            else
                static_cast<Bar*>(currentChartTab->getChart())->setCategories(CurrentTable, selections);
        }else{
            currentChartTab->setCategoriesRange();
            if(CandleStick* candleStickChart = dynamic_cast<CandleStick*>(currentChartTab->getChart()))
                candleStickChart->clearCategories();
            else
                static_cast<Bar*>(currentChartTab->getChart())->clearCategories();
        }
    }
}
void Controller::ChartRefresh(int row, int column){
    //Scorro tutte la tab di _Chart
    //Se l'elemento selezionato è nella posizione della cella del titolo
    //Modifico il titolo del grafico con quello dell'elemento selezionato
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QPair<int, int> cellPosition = QPair<int, int>(row+1, column+1);

    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        if(isInRange(cellPosition, currentTab->getTitlePosition())){
            currentTab->getChart()->setTitle(CurrentTable->item(row, column)->text());
        }
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            if(isInRange(cellPosition, candleStickTab->getOpeningPricesRange())){
                QPair<QPair<int,int>, QPair<int,int>> dataRange = candleStickTab->getOpeningPricesRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                static_cast<CandleStick*>(candleStickTab->getChart())->setOpeningPrices(CurrentTable, indexes);
            }
            if(isInRange(cellPosition, candleStickTab->getClosingPricesRange())){
                QPair<QPair<int,int>, QPair<int,int>> dataRange = candleStickTab->getClosingPricesRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                static_cast<CandleStick*>(candleStickTab->getChart())->setClosingPrices(CurrentTable, indexes);
            }
            if(isInRange(cellPosition, candleStickTab->getLowestPricesRange())){
                QPair<QPair<int,int>, QPair<int,int>> dataRange = candleStickTab->getLowestPricesRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                static_cast<CandleStick*>(candleStickTab->getChart())->setLowestPrices(CurrentTable, indexes);
            }
            if(isInRange(cellPosition, candleStickTab->getHighestPricesRange())){
                QPair<QPair<int,int>, QPair<int,int>> dataRange = candleStickTab->getHighestPricesRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                static_cast<CandleStick*>(candleStickTab->getChart())->setHighestPrices(CurrentTable, indexes);
            }
            if(isInRange(cellPosition, candleStickTab->getCategoriesRange())){
                QPair<QPair<int,int>, QPair<int,int>> dataRange = candleStickTab->getCategoriesRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                static_cast<CandleStick*>(candleStickTab->getChart())->setCategories(CurrentTable, indexes);
            }
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab))
                //Chart setting di tipo BarChart
                if(isInRange(cellPosition, barChart->getCategoriesRange()))
//                                        barChart->getChart->setCategories(CurrentTable,barChart->getCategoriesPositions());
                    return;
            if(isInRange(cellPosition, areaLinePieTab->getDataRange())){
                AreaLinePieSettings* currentChartTab = static_cast<AreaLinePieSettings*>(_MainWindow->getChartTab(i));
                QPair<QPair<int,int>, QPair<int,int>> dataRange = currentChartTab->getDataRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                currentChartTab->getChart()->setSeries(CurrentTable, indexes, currentChartTab->getParseMethod());
            }
            if(isInRange(cellPosition, areaLinePieTab->getLabelsRange())){
                AreaLinePieSettings* currentChartTab = static_cast<AreaLinePieSettings*>(_MainWindow->getChartTab(i));
                QPair<QPair<int,int>, QPair<int,int>> dataRange = currentChartTab->getLabelsRange();
                QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
                QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
                QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
                CurrentTable->clearSelection();
                if(userSelection.size()>0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);
                currentChartTab->getChart()->setLabels(CurrentTable, indexes);
            }
        }
    }
}
void Controller::parseMethodChange(QAbstractButton* btnClicked){
    //Controllo se la label del data range è diversa da unset
        //Sè e definita, seleziono gli elementi corrispondenti
        //Se il testo del pulsante è "Row Parsing"
            //Dico al grafico di aggiornare i dati con il flag di default
        //Altrimenti
            //Dico al grafico di recuperare i dati con il flag COLUMN
    //Altrimenti ritorno

    AreaLinePieSettings* currentChartTab = static_cast<AreaLinePieSettings*>(_MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex()));
    QPair<QPair<int,int>, QPair<int,int>> dataRange = currentChartTab->getDataRange();
    QPair<QPair<int,int>, QPair<int,int>> labelsRange = currentChartTab->getLabelsRange();

    if(dataRange.first.first != 0 && labelsRange.first.first !=0){
        QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
        QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
        QModelIndexList dataIndexes = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        CurrentTable->setRangeSelected(QTableWidgetSelectionRange(labelsRange.first.first-1, labelsRange.first.second-1, labelsRange.second.first-1, labelsRange.second.second-1), true);
        QModelIndexList labelsIndexes = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        if(userSelection.size() > 0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);

        if(btnClicked->text() == "Row Parsing") {
            currentChartTab->getChart()->setSeries(CurrentTable, dataIndexes);
            currentChartTab->getChart()->setLabels(CurrentTable, labelsIndexes);
        }else{
            currentChartTab->getChart()->setSeries(CurrentTable, dataIndexes, Flags::COLUMN);
            currentChartTab->getChart()->setLabels(CurrentTable, labelsIndexes, Flags::COLUMN);
        }
    }else if(dataRange.first.first != 0){
        QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
        QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
        QModelIndexList dataIndexes = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        if(userSelection.size() > 0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);

        if(btnClicked->text() == "Row Parsing") {
            currentChartTab->getChart()->setSeries(CurrentTable, dataIndexes);
        }else{
            currentChartTab->getChart()->setSeries(CurrentTable, dataIndexes, Flags::COLUMN);
        }
    }else if(labelsRange.first.first != 0){
        QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
        QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        CurrentTable->setRangeSelected(QTableWidgetSelectionRange(labelsRange.first.first-1, labelsRange.first.second-1, labelsRange.second.first-1, labelsRange.second.second-1), true);
        QModelIndexList labelsIndexes = CurrentTable->selectionModel()->selectedIndexes();
        CurrentTable->clearSelection();

        if(userSelection.size() > 0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);

        if(btnClicked->text() == "Row Parsing") {
            currentChartTab->getChart()->setLabels(CurrentTable, labelsIndexes);
        }else{
            currentChartTab->getChart()->setLabels(CurrentTable, labelsIndexes, Flags::COLUMN);
        }
    }


}
void Controller::themeChanged(int index){
    //Viene cambiato il theme del chart presente nella current tab di _Charts della current tab di _Files
    switch(index){
        case(0):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeLight);
        break;
        case(1):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeBlueCerulean);
        break;
        case(2):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeDark);
        break;
        case(3):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeBrownSand);
        break;
        case(4):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeBlueNcs);
        break;
        case(5):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeHighContrast);
        break;
        case(6):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeBlueIcy);
        break;
        case(7):
            _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->setTheme(QChart::ChartThemeQt);
        break;
        default:
        break;
    }

}
void Controller::chartReset(){
    _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->getChart()->clearData();
}
void Controller::toggleGuideWindow(){
    if(guideWindow){
        if(guideWindow->isVisible()) guideWindow->hide();
        else guideWindow->show();
    }
}
void Controller::sliceStandOut(){
    QPieSlice* slice = dynamic_cast<QPieSlice*>(QObject::sender());
    if(slice){
        if(slice->isExploded()) {
            slice->setExploded(false);
            slice->setLabelVisible(false);
        }else{
            slice->setExploded();
            slice->setLabelVisible();
        }
    }
}
void Controller::fileOpen(QString filePath){
    if (filePath == "") filePath = QFileDialog::getOpenFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
    if(_MainWindow->getFilePosition(QString("../"+(filePath.split("/")).last())) < 0){
        if (!(filePath.isEmpty()) && filePath.endsWith(QString(".crt"))){
            //Apro il file
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)){
                QByteArray data = file.readAll();
                file.close();
                QJsonDocument doc = QJsonDocument::fromJson(data);
                QJsonObject fullTab = doc.object();
                //Aggiungo una nuova tab pulita a _Files
                _MainWindow->newTab();
                //newTab mi porta la current tab nella posizione corretta
                //Setto il titolo con il nome del file
                _MainWindow->setCurrentTabTitle(QString("../"+(filePath.split("/")).last()));

                QTableWidget* table = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());

                QJsonObject cellList = fullTab["table"].toObject();
                for(int i=0; i<cellList.size(); i++){
                    QJsonObject cell = cellList[QString::number(i)].toObject();
                    QTableWidgetItem* newCell = new QTableWidgetItem();
                    QFont f = newCell->font();
                    f.setPointSize(cell["fontSize"].toInt());
                    newCell->setFont(f);
                    table->setItem(cell["row"].toInt(), cell["column"].toInt(), newCell);
                    table->item(cell["row"].toInt(), cell["column"].toInt())->setText(cell["value"].toString());
                }

                //per ogni entries creo un chart del tipo corrispondente su mainwindow
                QJsonObject chartList = fullTab["charts"].toObject();

                for(int i=0; i<chartList["chartNumber"].toInt(); i++){
                    QJsonObject chart = chartList[QString::number(i)].toObject();
                    QString type = chart["Type"].toString();
                    if(type == "CandleStick"){
                        _MainWindow->chartTypeSelected(Flags::CANDLESTICK);
                    }else if(type == "Bar"){
                        _MainWindow->chartTypeSelected(Flags::BARS);
                    }else{
                        if(type == "Area")
                            _MainWindow->chartTypeSelected(Flags::AREA);
                        else if(type == "Line")
                            _MainWindow->chartTypeSelected(Flags::LINES);
                        else
                            _MainWindow->chartTypeSelected(Flags::PIE);
                    }
                    _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->fromJSON(chart);
                    _MainWindow->getChartTab(_MainWindow->getCurrentChartTabIndex())->refresh(table);
                }

                //inserisco su _ActiveFiles il nuovo file
                _ActiveFiles.insert(QString("../"+(filePath.split("/")).last()), filePath);
            }
        }
    }
}
bool Controller::isInRange(QPair<int, int> pos, QPair<QPair<int, int>, QPair<int, int>> range){
    if((pos.first>=range.first.first && pos.first<=range.second.first) && (pos.second>=range.first.second && pos.second<=range.second.second)) return true;
    return false;
}
bool Controller::isInRange(QPair<int, int> pos1, QPair<int, int> pos2){
    return pos1 == pos2;
}
