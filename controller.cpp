#include "controller.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include<string>


Controller::Controller(): _MainWindow(new MainWindow(this)),  _ActiveFiles(QMap<QString, QString>()){
    lastSessionRestore();
    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->setAnimated(true);
    _MainWindow->show();
}

void Controller::recollectData(int index) const{
//    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
//    ChartSettings* chartPage = _MainWindow->getChartTab(index);
//    QPair<QPair<int, int>, QPair<int, int>> dataRange = chartPage->getDataRange();
//    QPieSeries* series = new QPieSeries();
//    //scorrimento per righe al momento
//    //recollecto per il pie chart
//    //idea fare recollect data diversa per ogni chart settings window e passare come parametri la modalità di scorrimento e l'array di elementidella tabella presi usanto get data range
//    for(int i=dataRange.first.first-1; i<dataRange.second.first; i++){
//        //NOTE:la funzione item di QTableWidget usa gli indici a partire da 0 !!!
//        QString sliceName = CurrentTable->item(i, dataRange.first.second-1)->text();
//        int sliceValue = 0;
//        for(int j=dataRange.first.second-1; j<dataRange.second.second; j++){
//            if(CurrentTable->item(i, j)){
//                if(isNumeric(CurrentTable->item(i, j)->text())){
//                    sliceValue+=CurrentTable->item(i, j)->text().toInt();
//                }else{
//                    //Segnalare all'utente che non c'è consistenza nel formato dei dati selezionati
//                }
//            }
//        }
//        qDebug() << i <<"crash test";
//        series->append(sliceName, sliceValue);
//    }

//    chartPage->getChart()->removeAllSeries();
//    //Removes and deletes all series objects that have been added to the chart. https://doc.qt.io/qt-5/qchart.html#removeAllSeries
//    chartPage->getChart()->addSeries(series);
}


void Controller::fileSave(int tableIndex, QString fileName){
    QString filePath = "";
    if(fileName==""){
        filePath = QFileDialog::getSaveFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
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
        tableJSON["ColNumber"] = table->columnCount();
        tableJSON["RowNumber"] = table->rowCount();

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

        int chartNumber = _MainWindow->getChartNumber(_MainWindow->getCurrentChartTabIndex())-1;
        QJsonObject charts;
        charts["chartNumber"] = chartNumber;
        for(auto i = 0; i<chartNumber; i++){
            ChartSettings* chartTab = _MainWindow->getChartTab(i);
            //Problemi nel save di un file senza focus
            charts["title"] = chartTab->getChart()->title();
            //a seconda del tipo devo poi tirarmi giù le diverse label
        }

        fullfile["charts"] = charts;
        //TODO : Salvare anche i grafici aperti?
        stream<<QJsonDocument(fullfile).toJson();
        file.close();
    }else{
        qDebug() << "Cannot Open file : "<<filePath;
    }
}
void Controller::UpperInsert(){
    _MainWindow->addRow();
}
void Controller::LowerInsert(){
    _MainWindow->addRow(Flags::DOWN);
}
void Controller::LeftInsert(){
    _MainWindow->addColumn();
}
void Controller::RightInsert(){
    _MainWindow->addColumn(Flags::RIGHT);
}
void Controller::TableReset(){
    QMessageBox::StandardButton Reply;
    Reply = QMessageBox::question(_MainWindow, "WARNING", "You are cleaning the entire table. Are you sure?", QMessageBox::Yes|QMessageBox::No);
    if(Reply == QMessageBox::Yes){
        _MainWindow->clearContent(Flags::ALL);
    }
};
void Controller::RowReset(){
    _MainWindow->clearContent(Flags::ROW);
};
void Controller::ColumnReset(){
    _MainWindow->clearContent(Flags::COLUMN);
};
void Controller::SelectionReset(){
    _MainWindow->clearContent(Flags::SELECTION);
};
void Controller::RowDelete(){
    _MainWindow->deleteContent();
};

void Controller::ColumnDelete(){
    _MainWindow->deleteContent(Flags::COLUMN);
};
void Controller::LeftAlign(){
    _MainWindow->textAlign();
};
void Controller::CenterAlign(){
    _MainWindow->textAlign(Flags::CENTER);
};
void Controller::RightAlign(){
    _MainWindow->textAlign(Flags::RIGHT);
};
void Controller::SpinBox(){
    _MainWindow->setSpinBox(10);
};

void Controller::SetTextSize(){
    _MainWindow->setTextSize(_MainWindow->getSpinValue());
};

void Controller::TabClose(int index){
    QString tabName = _MainWindow->getTabName(index);
    QMessageBox::StandardButton Reply;
    Reply = QMessageBox::question(_MainWindow, "Unsaved File", tabName+" may have usaved changes. Would you like to save them?", QMessageBox::Cancel|QMessageBox::Discard|QMessageBox::Save);
    if(Reply == QMessageBox::Save) fileSave(index, tabName=="Untitled" ? "" : tabName);
    else if(Reply == QMessageBox::Cancel) return;
    _ActiveFiles.remove(tabName);
    _MainWindow->closeTab(index);
};

void Controller::openFile(){
    fileOpen();
};

void Controller::saveACopy(){
    fileSave(_MainWindow->getCurrentTabIndex());
};

void Controller::newTab(){
    _MainWindow->newTab();
};

void Controller::saveFile(){
    fileSave(_MainWindow->getCurrentTabIndex(), _MainWindow->getTabName()=="Untitled" ? "" : _MainWindow->getTabName());
};

void Controller::mainWindowCloseEvent(){
    QFile file(QDir::currentPath()+"/cnfg.json");
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
        qDebug()<<"file cannot be opened";
    }
    _MainWindow->close();
};

void Controller::BarChartCreation(){
    _MainWindow->chartTypeSelected(Flags::BARS);
};

void Controller::CandleStickChartCreation(){
    _MainWindow->chartTypeSelected(Flags::CANDLESTICK);
};

void Controller::LineChartCreation(){
    _MainWindow->chartTypeSelected(Flags::LINES);
};

void Controller::PieChartCreation(){
    _MainWindow->chartTypeSelected(Flags::PIE);
};

void Controller::AreaChartCreation(){
    _MainWindow->chartTypeSelected(Flags::AREA);
};

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
        QTableWidgetItem* cellSelected = CurrentTable->item(newPosition.first, newPosition.second);
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
    //    currentChartTab->getChart()->setOpeningPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getOpeningPricesRange()){
            currentChartTab->setOpeningPricesRange(newPositions);
    //        currentChartTab->getChart()->setOpeningPrices(CurrentTable, newPositions);
        }else{
            currentChartTab->setOpeningPricesRange();
    //        currentChartTab->getChart()->setOpeningPrices();
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
    //    currentChartTab->getChart()->setClosingPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getClosingPricesRange()){
            currentChartTab->setClosingPricesRange(newPositions);
    //        currentChartTab->getChart()->setClosingPrices(CurrentTable, newPositions);
        }else{
            currentChartTab->setClosingPricesRange();
    //        currentChartTab->getChart()->clearClosingPrices();
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
    //    currentChartTab->getChart()->setHighestPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getLowestPricesRange()){
            currentChartTab->setLowestPricesRange(newPositions);
    //        currentChartTab->getChart()->setLowestPrices(CurrentTable, newPositions);
        }else{
            currentChartTab->setLowestPricesRange();
    //        currentChartTab->getChart()->clearHighestPrices();
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
    //    currentChartTab->getChart()->setHighestPrices();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getHighestPricesRange()){
            currentChartTab->setHighestPricesRange(newPositions);
    //        currentChartTab->getChart()->setHighestPrices(CurrentTable, newPositions);
        }else{
            currentChartTab->setHighestPricesRange();
    //        currentChartTab->getChart()->clearHighestPrices();
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
    //    currentChartTab->getChart()->setHighestPrices(); (static_castare a CandleStick)
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getCategoriesRange()){
            currentChartTab->setCategoriesRange(newPositions);
    //        currentChartTab->getChart()->setHighestPrices(CurrentTable, newPositions); (static_castare a CandleStick)
        }else{
            currentChartTab->setCategoriesRange();
    //        currentChartTab->getChart()->clearHighestPrices(); (static_castare a CandleStick)
        }
    }
}

void Controller::ChartRefresh(int row, int column){
    //Scorro tutte la tab di _Chart
    //Se l'elemento selezionato è nella posizione della cella del titolo
    //Modifico il titolo del grafico con quello dell'elemento selezionato
//    row++; column++;
    QTableWidget* CurrentTable = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QPair<int, int> cellPosition = QPair<int, int>(row, column);

    for (int i=0; i<_MainWindow->getChartNumber(_MainWindow->getCurrentTabIndex())-1; i++){
        ChartSettings* currentTab = _MainWindow->getChartTab(i);
        if(isInRange(cellPosition, currentTab->getTitlePosition())){
            currentTab->getChart()->setTitle(CurrentTable->item(row, column)->text());
        }
        if(CandleStickSettings* candleStickTab = dynamic_cast<CandleStickSettings*>(currentTab)){
            //Chart setting di tipo candlestic
            if(isInRange(cellPosition, candleStickTab->getOpeningPricesRange()))
                //                    candleStickTab->getChart->setOpeningPrices(CurrentTable,candleStickTab->getOpeningPricesPosition());
                return;
            if(isInRange(cellPosition, candleStickTab->getClosingPricesRange()))
                //                    candleStickTab->getChart->setClosingPrices(CurrentTable,candleStickTab->getClosingPricesPositions());
                return;
            if(isInRange(cellPosition, candleStickTab->getLowestPricesRange()))
                //                    candleStickTab->getChart->setLowestPrices(CurrentTable,candleStickTab->getLowestPricesPositions());
                return;
            if(isInRange(cellPosition, candleStickTab->getHighestPricesRange()))
                //                    candleStickTab->getChart->seHighestPrices(CurrentTable,candleStickTab->getHighestPricesPositions());
                return;
            if(isInRange(cellPosition, candleStickTab->getCategoriesRange()))
                //                    candleStickTab->getChart->setCategories(CurrentTable,candleStickTab->getCategoriesPositions());
                return;
        }else{
            AreaLinePieSettings* areaLinePieTab = dynamic_cast<AreaLinePieSettings*>(currentTab);
            if(BarSettings* barChart = dynamic_cast<BarSettings*>(currentTab))
                //Chart setting di tipo BarChart
                if(isInRange(cellPosition, barChart->getCategoriesRange()))
                    //                    barChart->getChart->setCategories(CurrentTable,barChart->getCategoriesPositions());
                    return;
            if(isInRange(cellPosition, areaLinePieTab->getDataRange()))
//                areaLinePieTab->getChart->setData(CurrentTable,areaLinePieTab->getDataRange(), areaLinePieTab->getParseMethod());
                return;
            if(isInRange(cellPosition, areaLinePieTab->getLabelsRange()))
//                areaLinePieTab->getChart->setLabels(CurrentTable,areaLinePieTab->getLabelsRange());
                return;
        }
    }
};

QTableWidget* Controller::fileParser(const QString filePath){
    QFile file(filePath);
    QTableWidget* parsedTable = nullptr;
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject table = doc.object();
        parsedTable = new QTableWidget(table.value("RowNumber").toInt(), table.value("ColNumber").toInt());

        for(int i=0; i<table.size()-2; i++){
            QJsonObject cellJSON = table.value(QString::number(i)).toObject();
            cellJSON.value("fontSize").toInt();
            QTableWidgetItem* cell = new QTableWidgetItem;

            cell->setText(cellJSON.value("value").toString());

            QFont makeAF = cell->font();
            makeAF.setPointSize(cellJSON.value("fontSize").toInt());
            cell->setFont(makeAF);

            parsedTable->setItem(cellJSON.value("row").toInt(), cellJSON.value("column").toInt(), cell);
        }
    }
    return parsedTable;
};

void Controller::lastSessionRestore(){
    QFile file(QDir::currentPath()+"/cnfg.json");
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
};

void Controller::fileOpen(QString filePath){
    if (filePath == "") filePath = QFileDialog::getOpenFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
    if(_MainWindow->getFilePosition(QString("../"+(filePath.split("/")).last())) < 0){
        if (!(filePath.isEmpty()) && filePath.endsWith(QString(".crt"))){
            _MainWindow->openFile(QString("../"+(filePath.split("/")).last()), fileParser(filePath));
            _ActiveFiles.insert(QString("../"+(filePath.split("/")).last()), filePath);
        }
    }
}

bool Controller::isNumeric(QString string) const{
    QRegExp regex("^[0-9]\\d*(\\.\\d+)?$");
    return regex.exactMatch(string);
}

bool Controller::isInRange(QPair<int, int> pos, QPair<QPair<int, int>, QPair<int, int>> range){
    if((pos.first>=range.first.first && pos.first<=range.second.first) && (pos.second>=range.first.second && pos.second<=range.second.second)) return true;
    return false;
}

bool Controller::isInRange(QPair<int, int> pos1, QPair<int, int> pos2){
    return pos1 == pos2;
};
