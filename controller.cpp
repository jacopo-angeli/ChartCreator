#include "controller.h"
#include "candlestick.h"
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include<string>
#include "area.h"
Controller::Controller(): _MainWindow(new MainWindow(this)),  _ActiveFiles(QMap<QString, QString>()){
    lastSessionRestore();
    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->setAnimated(true);
    _MainWindow->show();
}
bool Controller::fileSave(int tableIndex, QString fileName){
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
    if(Reply == QMessageBox::Save){
        if(fileSave(index, tabName=="Untitled" ? "" : tabName)){
            _MainWindow->closeTab(index);
            if(tabName != "Untitled") _ActiveFiles.remove(tabName);
        }
    }else if(Reply == QMessageBox::Discard){
        _MainWindow->closeTab(index);
        if(tabName != "Untitled") _ActiveFiles.remove(tabName);
    }
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
//        std::cout<<"file cannot be opened";
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
//        else
//            static_cast<Bar*>(currentChartTab->getChart())->clearCategories();
    }else{
        QPair<QPair<int, int>, QPair<int, int>> newPositions = QPair<QPair<int, int>, QPair<int, int>>(QPair<int, int>((selections.first().row()+1),(selections.first().column()+1)),QPair<int, int>((selections.last().row()+1),(selections.last().column()+1)));
        if(newPositions != currentChartTab->getCategoriesRange()){
            currentChartTab->setCategoriesRange(newPositions);
            if(CandleStick* candleStickChart = dynamic_cast<CandleStick*>(currentChartTab->getChart()))
                candleStickChart->setCategories(CurrentTable, selections);
    //        else
    //            static_cast<Bar*>(currentChartTab->getChart())->setCategories(CurrentTable, selections);
        }else{
            currentChartTab->setCategoriesRange();
            if(CandleStick* candleStickChart = dynamic_cast<CandleStick*>(currentChartTab->getChart()))
                candleStickChart->clearCategories();
    //        else
    //            static_cast<Bar*>(currentChartTab->getChart())->clearCategories();
        }
    }
}
void Controller::ChartRefresh(int row, int column){
    //Scorro tutte la tab di _Chart
    //Se l'elemento selezionato è nella posizione della cella del titolo
    //Modifico il titolo del grafico con quello dell'elemento selezionato
//    row++; column++;
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
                    //                    barChart->getChart->setCategories(CurrentTable,barChart->getCategoriesPositions());
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
    if(dataRange.first.first == 0) return; //Label "Unset"

    QTableWidget* CurrentTable= _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());
    QModelIndexList userSelection = CurrentTable->selectionModel()->selectedIndexes();
    CurrentTable->clearSelection();
    CurrentTable->setRangeSelected(QTableWidgetSelectionRange(dataRange.first.first-1, dataRange.first.second-1, dataRange.second.first-1, dataRange.second.second-1), true);
    QModelIndexList indexes = CurrentTable->selectionModel()->selectedIndexes();
    CurrentTable->clearSelection();

    if(userSelection.size() > 0) CurrentTable->setRangeSelected(QTableWidgetSelectionRange(userSelection.first().row(),userSelection.first().column(), userSelection.last().row(), userSelection.last().column()), true);

    if(btnClicked->text() == "Row Parsing") currentChartTab->getChart()->setSeries(CurrentTable, indexes);
    else currentChartTab->getChart()->setSeries(CurrentTable, indexes, Flags::COLUMN);
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
void Controller::chartCreationGuide(){

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
    qDebug() << filePath;
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
                }

                //riempio le celle salvate sul json così trigghero il refresh dei grafici
                QTableWidget* table = _MainWindow->getFullTable(_MainWindow->getCurrentTabIndex());

                QJsonObject cellList = fullTab["table"].toObject();
                for(int i=0; i<cellList.size(); i++){
                    QJsonObject cell = cellList[QString::number(i)].toObject();
                    QTableWidgetItem* newCell = new QTableWidgetItem();
                    newCell->setText(cell["value"].toString());
                    QFont f = newCell->font();
                    f.setPointSize(cell["fontSize"].toInt());
                    newCell->setFont(f);
                    table->setItem(cell["row"].toInt(), cell["column"].toInt(), newCell);
                }

                //inserisco su _ActiveFiles il nuovo file
                _ActiveFiles.insert(QString("../"+(filePath.split("/")).last()), filePath);
            }
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
}
