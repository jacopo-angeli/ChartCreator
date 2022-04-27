#include "controller.h"


Controller::Controller(): _MainWindow(new MainWindow(this)), _ChartWindows(QVector<ChartWindow*>()), _ChartSelection(new ChartSelection()), _ChartSettings(new ChartSettings()){
    _MainWindow->setWindowState(Qt::WindowMaximized);
    _MainWindow->show();
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
    Reply = QMessageBox::question(this, "WARNING", "You are cleaning the entire table. Are you sure?", QMessageBox::Yes|QMessageBox::No /*"CONTINUE?", "You are cleaing the entire table. Are you sure?", QMessageBox::Yes|QMessageBox::No*/);
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
    _MainWindow->setSpinBox();
}

void Controller::setTextSize(){
    _MainWindow->setTextSize();
}

void Controller::newSheet()
{

};
