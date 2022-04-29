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
    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->show();
}

void Controller::saveFile(int tableIndex){
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

void Controller::overwriteFile(QString fileName, int tableIndex){
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
        _MainWindow->clearContent();
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
    Reply = QMessageBox::question(_MainWindow, "Unsaved File", tabName+" have unsaved change.", QMessageBox::Save|QMessageBox::Discard);
    if(Reply == QMessageBox::Save){
        if(tabName == "Untitled"){
            saveFile(index);
        }else{
            overwriteFile(tabName, index);
            _ActiveFiles.remove(tabName);
        }
    }
    _MainWindow->closeTab(index);
}

void Controller::openFile(){
    QString filePath = QFileDialog::getOpenFileName(_MainWindow, QString("Open file"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), tr("ChartCreator (*.crt)"));
    if (!(filePath.isEmpty()) && filePath.endsWith(QString(".crt"))){
        _MainWindow->openFile(QString("../"+(filePath.split("/")).last()), fileParser(filePath));
        _ActiveFiles.insert(QString("../"+(filePath.split("/")).last()), filePath);
    }

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
