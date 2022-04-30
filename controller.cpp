#include "controller.h"

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include<string>


Controller::Controller(): _MainWindow(new MainWindow(this)), _ChartWindows(QVector<ChartWindow*>()), _ChartSelection(new ChartSelection()), _ChartSettings(new ChartSettings()), _ActiveFiles(QMap<QString, QString>()){
    //aprire il file di config
    //controllare se c'erano file aperti
    //aprire tutti i file della scorsa sessione
    //se non c'erano file aperti, aprire untitled
    lastSessionRestore();
    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->setAnimated(true);
    _MainWindow->show();
}

void Controller::fileSave(int tableIndex){
    QString filePath = QFileDialog::getSaveFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
    if(!(filePath.contains(".crt"))) filePath.append(".crt");;
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream stream(&file);
        QJsonObject obj;
        QTableWidget* table = _MainWindow->getFullTable(tableIndex);
        obj.insert("ColNumber", table->columnCount());
        obj.insert("RowNumber", table->rowCount());

        table->selectAll();
        QList<QTableWidgetItem*> ItemList = table->selectedItems();
        table->clearSelection();

        int i=0;
        for(auto it = ItemList.begin(); it != ItemList.end(); it++){
            QJsonObject cell;
            cell.insert("row", (*it)->row());
            cell.insert("column", (*it)->column());
            cell.insert("value", (*it)->text());
            QFont f = (*it)->font();
            cell.insert("fontSize",f.pointSize());
            obj.insert(QString::number(i), cell);
            i++;
        }
        stream<<QJsonDocument(obj).toJson();
        file.close();
    }else{
        //error
    }
}

void Controller::fileOverwrite(QString fileName, int tableIndex){
    QFile file(_ActiveFiles[fileName]);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QTextStream stream(&file);
        QJsonObject obj;
        QTableWidget* table = _MainWindow->getFullTable(tableIndex);
        obj.insert("ColNumber", table->columnCount());
        obj.insert("RowNumber", table->rowCount());

        table->selectAll();
        QList<QTableWidgetItem*> ItemList = table->selectedItems();
        table->clearSelection();

        int i=0;
        for(auto it = ItemList.begin(); it != ItemList.end(); it++){
            QJsonObject cell;
            cell.insert("row", (*it)->row());
            cell.insert("column", (*it)->column());
            cell.insert("value", (*it)->text());
            QFont f = (*it)->font();
            cell.insert("fontSize",f.pointSize());
            obj.insert(QString::number(i), cell);
            i++;
        }
        stream<<QJsonDocument(obj).toJson();
        file.close();
    }else{
        //error
    }
}


void Controller::NewChart(){
}
void Controller::ChangeChart(){

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
}

void Controller::RowDelete(){
    _MainWindow->deleteContent();
}

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
}

void Controller::setTextSize(){
    _MainWindow->setTextSize(_MainWindow->getSpinValue());
}

void Controller::tabClose(int index){
    QString tabName = _MainWindow->getTabName(index);
    QMessageBox::StandardButton Reply;
    Reply = QMessageBox::question(_MainWindow, "Unsaved File", tabName+" may have usaved changes. Would you like to save them?", QMessageBox::Cancel|QMessageBox::Discard|QMessageBox::Save);
    if(Reply == QMessageBox::Save){
        if(tabName == "Untitled"){
            fileSave(index);
        }else{
            fileOverwrite(tabName, index);
        }
    }else if(Reply == QMessageBox::Cancel){
        return;
    }
    _ActiveFiles.remove(tabName);
    _MainWindow->closeTab(index);
}

void Controller::openFile(){
    fileOpen();
}

void Controller::newTab(){

}

void Controller::overwrite(){
    //parsa la current tab di _Tabs e sovrascrive il file aperto
    //ho bisogno della path completa del current file
    //ho bisogno che la tab non sia nuova
    //distigunere il caso della prima apertura del file
    if(_MainWindow->getCurrentTabName() != QString("Untitled")){

    }else{

    }
}

void Controller::mainWindowCloseEvent(){
    QFile file(QDir::currentPath()+"/cnfg.json");
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        QFileInfo fInfo = QFileInfo(file);
        qDebug() << "file opened. Location : " << fInfo.absoluteFilePath();
        QTextStream stream(&file);
        QJsonObject obj;
        obj.insert("File number", _ActiveFiles.size());
        int i=0;
        for (auto it = _ActiveFiles.begin(); it!=_ActiveFiles.end() ; it++) {
            qDebug() << it.value() <<" stored; /n";
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
}

void Controller::lastSessionRestore(){
    QFile file(QDir::currentPath()+"/cnfg.json");
    if (file.open(QIODevice::ReadOnly)){
        QByteArray data = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject lastArrayState = doc.object();
        qDebug() << lastArrayState.size()-1 << " file to open; \n";
        for(int i=0; i<lastArrayState.size()-1; i++){
            QJsonObject keyValuePair = lastArrayState.value(QString("File ")+QString::number(i)).toObject();
            fileOpen(keyValuePair.value("path").toString());
//            qDebug() << keyValuePair.value("key").toString() << keyValuePair.value("path").toString() << " inserted; \n";
//            _ActiveFiles.insert(keyValuePair.value("key").toString(), keyValuePair.value("path").toString());
        }
    }
}

void Controller::fileOpen(QString filePath){
    if (filePath == "") filePath = QFileDialog::getOpenFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
    if (!(filePath.isEmpty()) && filePath.endsWith(QString(".crt"))){
        _MainWindow->openFile(QString("../"+(filePath.split("/")).last()), fileParser(filePath));
        _ActiveFiles.insert(QString("../"+(filePath.split("/")).last()), filePath);
    }
}
