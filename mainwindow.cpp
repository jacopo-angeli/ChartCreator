#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), _Tab(new QTabWidget()), _Table(new QTableWidget(50,50)), _ValidatorFlag(0){
    QMenuBar *MenuBar = new QMenuBar(this);

    QMenu *File = new QMenu("&File", MenuBar);
    QMenu *Tools = new QMenu("&Tools", MenuBar);
    QMenu *Help = new QMenu("&Help", MenuBar);

    QAction *NewWorkSheet = new QAction("&New WorkSheet", File);
    NewWorkSheet->setShortcut(QKeySequence::New);
//    connect(NewWorkSheet, SIGNAL(triggered()), this, SLOT(NewWorkSheet()));
    File->addAction(NewWorkSheet);
    File->addAction(new QAction("&Open WorkSheet...", File));

    File->addSeparator();
    File->addAction(new QAction("Over&write File", File));
    QAction *SaveCsvCopy = new QAction("&Save a copy", File);
    SaveCsvCopy->setShortcut(QKeySequence::Save);
//    connect(SaveCsvCopy, SIGNAL(triggered()), this, SLOT(SaveCsvCopy()));
    File->addAction(SaveCsvCopy);
    File->addSeparator();
    File->addAction(new QAction("&Print", File));
    File->addSeparator();

    QAction *Quit = new QAction("&Quit", File);
    Quit->setShortcut(QKeySequence::Quit);
//    connect(Quit, SIGNAL(triggered()), this, SLOT(close()));
    File->addAction(Quit);

    Help->addAction(new QAction("Usage &Manual", Help));
    Help->addAction(new QAction("&Contacts", Help));

    File->setMinimumWidth(getMaxMenuSize(File) * 1.5);
    Tools->setMinimumWidth(getMaxMenuSize(Tools) * 1.5);
    Help->setMinimumWidth(getMaxMenuSize(Help) * 1.5);
    MenuBar->addMenu(File);
    MenuBar->addMenu(Tools);
    MenuBar->addMenu(Help);

    setMenuBar(MenuBar);

    QToolBar *ToolBar = new QToolBar("Toolbar");
    QToolButton *NewRow = new QToolButton(ToolBar);
    NewRow->setText("New Row");
    NewRow->setIcon(QIcon("../ProgettoPao_21_22/icons/NewRow.png"));
    NewRow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewRow->setPopupMode(QToolButton::InstantPopup);
    QAction *UpperInsert = new QAction("Upper Insert", NewRow);
    QAction *LowerInsert = new QAction("Lower Insert", NewRow);
    NewRow->addAction(UpperInsert);
    NewRow->addAction(LowerInsert);
//    connect(UpperInsert, SIGNAL(triggered()), this, SLOT(UpperInsert()));
//    connect(LowerInsert, SIGNAL(triggered()), this, SLOT(LowerInsert()));

    QToolButton *NewColumn = new QToolButton(ToolBar);
    NewColumn->setText("New Column");
    NewColumn->setIcon(QIcon("../ProgettoPao_21_22/icons/NewColumn.png"));
    NewColumn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewColumn->setPopupMode(QToolButton::InstantPopup);
    QAction *RightInsert = new QAction("Right Insert", NewColumn);
    QAction *LeftInsert = new QAction("Left Insert", NewColumn);
    NewColumn->addAction(RightInsert);
    NewColumn->addAction(LeftInsert);
//    connect(RightInsert, SIGNAL(triggered()), this, SLOT(RightInsert()));
//    connect(LeftInsert, SIGNAL(triggered()), this, SLOT(LeftInsert()));

    QToolButton *Clear = new QToolButton(ToolBar);
    Clear->setText("Eraser");
    Clear->setIcon(QIcon("../ProgettoPao_21_22/icons/Erase.png"));
    Clear->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Clear->setPopupMode(QToolButton::InstantPopup);
    QAction *ClearSelection = new QAction("Clear current selection", Clear);
    ClearSelection->setShortcut(QKeySequence::Delete);
    QAction *ClearColumn = new QAction("Clear current column", Clear);
    QAction *ClearRow = new QAction("Clear current row", Clear);
    Clear->addAction(ClearSelection);
    Clear->addAction(ClearColumn);
    Clear->addAction(ClearRow);
//    connect(ClearSelection, SIGNAL(triggered()), this, SLOT(ClearSelection()));
//    connect(ClearColumn, SIGNAL(triggered()), this, SLOT(ClearColumn()));
//    connect(ClearRow, SIGNAL(triggered()), this, SLOT(ClearRow()));

    QToolButton *Delete = new QToolButton(ToolBar);
    Delete->setText("Delete");
    Delete->setIcon(QIcon("../ProgettoPao_21_22/icons/Delete.png"));
    Delete->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Delete->setPopupMode(QToolButton::InstantPopup);
    QAction *ColumnDeleting = new QAction("Delete selected column", Delete);
    QAction *RowDeleting = new QAction("Delete selected row", Delete);
    Delete->addAction(ColumnDeleting);
    Delete->addAction(RowDeleting);
//    connect(ColumnDeleting, SIGNAL(triggered()), this, SLOT(DeleteColumn()));
//    connect(RowDeleting, SIGNAL(triggered()), this, SLOT(DeleteRow()));

    QToolButton *TableReset = new QToolButton(ToolBar);
    TableReset->setText("Reset Table");
    TableReset->setIcon(QIcon("../ProgettoPao_21_22/icons/Reset.png"));
    TableReset->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    TableReset->setPopupMode(QToolButton::InstantPopup);
//    connect(TableReset, SIGNAL(clicked()), this, SLOT(TableResetAlert()));

    QToolButton *TextAlignment = new QToolButton(ToolBar);
    TextAlignment->setText("Text Align");
    TextAlignment->setIcon(QIcon("../ProgettoPao_21_22/icons/TextSettings.png"));
    TextAlignment->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    TextAlignment->setPopupMode(QToolButton::InstantPopup);
    QAction *LeftAlign = new QAction("Align left",TextAlignment);
    LeftAlign->setIcon(QIcon("../ProgettoPao_21_22/icons/LeftAlign.png"));
    QAction *CenterAlign = new QAction("Align center",TextAlignment);
    CenterAlign->setIcon(QIcon("../ProgettoPao_21_22/icons/CenterAlign.png"));
    QAction *RightAlign = new QAction("Align right",TextAlignment);
    RightAlign->setIcon(QIcon("../ProgettoPao_21_22/icons/RightAlign.png"));
//    connect(LeftAlign, SIGNAL(triggered()), this, SLOT(LeftAlign()));
//    connect(CenterAlign, SIGNAL(triggered()), this, SLOT(CenterAlign()));
//    connect(RightAlign, SIGNAL(triggered()), this, SLOT(RightAlign()));
    TextAlignment->addAction(LeftAlign);
    TextAlignment->addAction(CenterAlign);
    TextAlignment->addAction(RightAlign);

    QToolButton *NewGraph = new QToolButton(ToolBar);
    NewGraph->setText("Create Graph");
    NewGraph->setIcon(QIcon("../ProgettoPao_21_22/icons/NewGraph.png"));
    NewGraph->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewGraph->setPopupMode(QToolButton::InstantPopup);
//    connect(NewGraph, SIGNAL(clicked()), this, SLOT(OpenGraphWindow()));

    _TxtDim = new QSpinBox(ToolBar);
    _TxtDim->setSpecialValueText("-");
//    connect(_TxtDim, SIGNAL(valueChanged(int)), this, SLOT(SetTextSize()));

    NewColumn->setMinimumWidth(110);
    NewColumn->setStyleSheet("margin:5px;");
    NewRow ->setMinimumWidth(110);
    NewRow->setStyleSheet("margin:5px;");
    Clear->setMinimumWidth(110);
    Clear->setStyleSheet("margin:5px;");
    Delete->setMinimumWidth(110);
    Delete->setStyleSheet("margin:5px;");
    TableReset->setMinimumWidth(110);
    TableReset->setStyleSheet("margin:5px;");
    NewGraph->setMinimumWidth(110);
    NewGraph->setStyleSheet("margin:5px;");
    TextAlignment->setMinimumWidth(110);
    TextAlignment->setStyleSheet("margin:5px;");
    _TxtDim->setMinimumWidth(110);
    _TxtDim->setStyleSheet("margin:5px;");

    _Tab->addTab(_Table, QString("Sheet &1"));
    _Tab->addTab(new QTableWidget(50,50), QString("New Sheet"));
//    connect(_Tab, SIGNAL(tabBarClicked(int)), this, SLOT(addTab(int)));
//    connect(_Table, SIGNAL(itemSelectionChanged()), this, SLOT(SpinBoxRefresh()));
//    connect(_Table, SIGNAL(cellChanged(int,int)), this, SLOT(CellValidator(int,int)));
    setCentralWidget(_Tab);

    ToolBar->addWidget(NewRow);
    ToolBar->addWidget(NewColumn);
    ToolBar->addSeparator();
    ToolBar->addWidget(Clear);
    ToolBar->addWidget(Delete);
    ToolBar->addWidget(TableReset);
    ToolBar->addSeparator();
    ToolBar->addWidget(TextAlignment);
    ToolBar->addWidget(_TxtDim);
    ToolBar->addSeparator();
    ToolBar->addWidget(NewGraph);
    addToolBar(Qt::LeftToolBarArea, ToolBar);
}

void MainWindow::addRow(Flags dir)
{
    switch (dir) {
        case (Flags::TOP):
            _Table->insertRow(_Table->currentRow());
        break;
        case (Flags::DOWN):
            _Table->insertRow(_Table->currentRow()+1);
        break;
        default:
        break;
    }
}

void MainWindow::addColumn(Flags dir)
{
    switch (dir) {
        case (Flags::LEFT):
            _Table->insertColumn(_Table->currentColumn()+1);
        break;
        case (Flags::RIGHT):
            _Table->insertColumn(_Table->currentColumn());
        break;
        default:
        break;
    }
}

void MainWindow::clearTable()
{
    _Table->clearContents();
}

void MainWindow::clearContent(Flags Content)
{
    switch (Content) {
        case (Flags::SELECTION): {
            QList<QTableWidgetItem*> ItemList = _Table->selectedItems();
            for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
                QTableWidgetItem *element = *it;
                element->setText("");
            }
        }
            break;

        case (Flags::COLUMN):{
            int currentIndex = _Table->currentColumn();
            for(int i=0; i<_Table->rowCount(); i++){
                QTableWidgetItem *TI = _Table->item(i, currentIndex);
                if(TI) TI->setText("");
            }
        }
            break;

        case (Flags::ROW):{
            int currentIndex = _Table->currentRow();
            for(int i=0; i<_Table->columnCount(); i++){
                QTableWidgetItem *TI = _Table->item(currentIndex, i);
                if(TI) TI->setText("");
            }
        }
            break;

        default:
            break;
    }
}

void MainWindow::deleteContent(Flags Content)
{
    switch (Content) {
        case (Flags::ROW):
            _Table->removeColumn(_Table->currentColumn());
            break;
        case (Flags::COLUMN):
            _Table->removeRow(_Table->currentRow());
            break;
        default:
            break;
    }
}

void MainWindow::textAlign(Flags dir)
{
    QList<QTableWidgetItem*> ItemList = _Table->selectedItems();
    switch (dir) {
        case(Flags::LEFT):{
            for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
                QTableWidgetItem *element = *it;
                element->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
            }
        }
            break;
        case(Flags::CENTER):{
            for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
                QTableWidgetItem *element = *it;
                element->setTextAlignment(Qt::AlignCenter | Qt::AlignVCenter);
            }
        }
            break;
        case(Flags::RIGHT):{
            for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
                QTableWidgetItem *element = *it;
                element->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            }
        }
            break;
        default:
            break;
    }
}

void MainWindow::setSpinBox()
{
//    _TxtDim->setValue(getTextSize());
    _TxtDim->setValue(10);
}

void MainWindow::setTextSize()
{
    QFont TFont= _Table->font();
    TFont.setPointSize(_TxtDim->value());
    QList<QTableWidgetItem*> ItemList = _Table->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
        QTableWidgetItem *element = *it;
        element->setFont(TFont);
    }
}

int MainWindow::getMaxMenuSize(QMenu *MenuBar){
    int v=0;
    foreach (QAction *action, MenuBar->actions()){
        QFontMetrics metrics(action->font());
        int T2P = metrics.lineWidth();
        v = (v < T2P ? T2P : v);
    }
    return v;
}

int MainWindow::getTextSize()
{
    int size=0;
    QList<QTableWidgetItem*> ItemList = _Table->selectedItems();
    if(!(ItemList.isEmpty())){
        for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
            QTableWidgetItem *element = *it;
            if(element){
                QFont tmp = element->font();
                if(size == 0){
                    size = tmp.pointSize();
                }else{
                    if(tmp.pointSize() != size){
                        size = 0;
                        break;
                    }
                }
            }
        }
    }
    return size;
}

//void MainWindow::CellValidator(int row, int column){
//   if(row!=0 && column!=0){
//       QTableWidgetItem *Item = _Table->item(row, column);
//       QRegExp re("[+-]?([0-9]*[.])?[0-9]+");
//       QRegExp reDate("^(0[1-9]|[12][0-9]|3[01])[- /.](0[1-9]|1[012])[- /.](19|20)\\d\\d$");
//        if(Item){
//            if(Item->backgroundColor() == QColor(255, 0, 0, 100)){
//                if(re.exactMatch(Item->text()) || reDate.exactMatch(Item->text())){
//                    _ValidatorFlag--;
//                    Item->setBackgroundColor(QColor(255, 255, 255));
//                }else if(Item->text().toStdString() == ""){
//                    _ValidatorFlag--;
//                    Item->setBackgroundColor(QColor(255, 255, 255));
//                }
//            }else{
//                if(!(reDate.exactMatch(Item->text()) || re.exactMatch(Item->text()))){
//                    if(Item->text().toStdString() != ""){
//                        _ValidatorFlag++;
//                        Item->setBackgroundColor(QColor(255, 0, 0, 100));
//                    }
//                }
//            }
//       }
//   }
//}

//void MainWindow::NewWorkSheet(){
//    std::cout<<"asdadsa"<<std::endl;
//}
//void MainWindow::addTab(int index){
//    std::cout<<index<<std::endl<<_Tab->count()<<std::endl;
//    if((index+1) == _Tab->count()){
//        _Tab->setTabText(index, QString("Sheet &"+QString::number(index+1)));
//        _Tab->addTab(new QTableWidget(50,50), QString("New Sheet"));
//    }
//}
//void MainWindow::SaveCsvCopy(){
//    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation),tr("ChartCreator (*.crt)"));
//    //check if user typed .crt
//    if(!(fileName.contains(".crt"))) fileName.append(".crt");

//    if(TableParser(fileName)){
//       std::cout<<"success"<<std::endl;
//    };
//    std::cout<<fileName.toStdString()<<std::endl;
//}

//bool MainWindow::TableParser(const QString& fileName){
//    //Create file
//    QFile file(fileName);
//    //Open file
//    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate)) {
//        QTextStream stream(&file);
//        //file successfully opened
//        //table parse into the file

//        QJsonArray JRows;
//        for(int i=0; i<_Table->rowCount(); i++){
//            _Table->selectRow(i);
//            QList<QTableWidgetItem*> ItemList = _Table->selectedItems();
//            QJsonArray JRowi;
//            for(int j=0; j<ItemList.length(); j++){

//                if(ItemList[j]->text()!=""){

//                    QJsonObject ItemJ;
//                    ItemJ.insert("row", i);
//                    ItemJ.insert("column", j);
//                    ItemJ.insert("value", ItemList[j]->text());
//                    ItemJ.insert("color", ItemList[j]->backgroundColor().value());
//                    QFont f = ItemList[j]->font();
//                    ItemJ.insert("fontSize",f.pointSize());
//                    ItemJ.insert("NewLine", false);

//                    JRowi.append(ItemJ);
//                }
//            }

//            QJsonObject NewLine;
//            NewLine.insert("NewLine", true);
//            JRowi.append(NewLine);

//            JRows.append(JRowi);
//        }
//        stream <<QJsonDocument(JRows).toJson();

//        _Table->setCurrentCell(0,0);

//        return true;
//    } else return false;
//}
