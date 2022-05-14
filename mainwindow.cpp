#include "mainwindow.h"
#include <QHBoxLayout>
#include <typeinfo>
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), _Files(new QTabWidget()){
    QMenuBar *MenuBar = new QMenuBar(this);

    QMenu *File = new QMenu("&File", MenuBar);
    QMenu *Tools = new QMenu("&Tools", MenuBar);
    QMenu *Help = new QMenu("&Help", MenuBar);

    QAction *NewTab = new QAction("&New File", File);
    NewTab->setShortcut(QKeySequence::New);
    connect(NewTab, SIGNAL(triggered()), parent, SLOT(newTab()));
    File->addAction(NewTab);

    QAction *OpenFile = new QAction("&Open File", File);
    OpenFile->setShortcut(QKeySequence::Open);
    connect(OpenFile, SIGNAL(triggered()), parent, SLOT(openFile()));
    File->addAction(OpenFile);

    File->addSeparator();

    QAction *Save = new QAction("&Save", File);
    Save->setShortcut(QKeySequence::Save);
    connect(Save, SIGNAL(triggered()), parent, SLOT(saveFile()));
    File->addAction(Save);

    QAction *SaveACopy = new QAction("&Save a copy", File);
    SaveACopy->setShortcut(QKeySequence::SaveAs);
    connect(SaveACopy, SIGNAL(triggered()), parent, SLOT(saveACopy()));
    File->addAction(SaveACopy);

    File->addSeparator();

    File->addAction(new QAction("&Print", File));
    /*TODO : Print command*/

    File->addSeparator();

    QAction *Quit = new QAction("&Quit", File);
    Quit->setShortcut(QKeySequence::Quit);
    connect(Quit, SIGNAL(triggered()), parent, SLOT(close()));
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
    NewRow->setIcon(QIcon("../OOPPROJECT/icons/NewRow.png"));
    NewRow->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewRow->setPopupMode(QToolButton::InstantPopup);
    QAction *UpperInsert = new QAction("Upper Insert", NewRow);
    QAction *LowerInsert = new QAction("Lower Insert", NewRow);
    NewRow->addAction(UpperInsert);
    NewRow->addAction(LowerInsert);
    connect(UpperInsert, SIGNAL(triggered()), parent, SLOT(UpperInsert()));
    connect(LowerInsert, SIGNAL(triggered()), parent, SLOT(LowerInsert()));

    QToolButton *NewColumn = new QToolButton(ToolBar);
    NewColumn->setText("New Column");
    NewColumn->setIcon(QIcon("../OOPPROJECT/icons/NewColumn.png"));
    NewColumn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewColumn->setPopupMode(QToolButton::InstantPopup);
    QAction *RightInsert = new QAction("Right Insert", NewColumn);
    QAction *LeftInsert = new QAction("Left Insert", NewColumn);
    NewColumn->addAction(RightInsert);
    NewColumn->addAction(LeftInsert);
    connect(RightInsert, SIGNAL(triggered()), parent, SLOT(RightInsert()));
    connect(LeftInsert, SIGNAL(triggered()), parent, SLOT(LeftInsert()));

    QToolButton *Clear = new QToolButton(ToolBar);
    Clear->setText("Eraser");
    Clear->setIcon(QIcon("../OOPPROJECT/icons/Erase.png"));
    Clear->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Clear->setPopupMode(QToolButton::InstantPopup);
    QAction *ClearSelection = new QAction("Clear current selection", Clear);
    ClearSelection->setShortcut(QKeySequence::Delete);
    QAction *ClearColumn = new QAction("Clear current column", Clear);
    QAction *ClearRow = new QAction("Clear current row", Clear);
    Clear->addAction(ClearSelection);
    Clear->addAction(ClearColumn);
    Clear->addAction(ClearRow);
    connect(ClearSelection, SIGNAL(triggered()), parent, SLOT(SelectionReset()));
    connect(ClearColumn, SIGNAL(triggered()), parent, SLOT(ColumnReset()));
    connect(ClearRow, SIGNAL(triggered()), parent, SLOT(RowReset()));

    QToolButton *Delete = new QToolButton(ToolBar);
    Delete->setText("Delete");
    Delete->setIcon(QIcon("../OOPPROJECT/icons/Delete.png"));
    Delete->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    Delete->setPopupMode(QToolButton::InstantPopup);
    QAction *ColumnDeleting = new QAction("Delete selected column", Delete);
    QAction *RowDeleting = new QAction("Delete selected row", Delete);
    Delete->addAction(ColumnDeleting);
    Delete->addAction(RowDeleting);
    connect(ColumnDeleting, SIGNAL(triggered()), parent, SLOT(ColumnDelete()));
    connect(RowDeleting, SIGNAL(triggered()), parent, SLOT(RowDelete()));

    QToolButton *TableReset = new QToolButton(ToolBar);
    TableReset->setText("Reset Table");
    TableReset->setIcon(QIcon("../OOPPROJECT/icons/Reset.png"));
    TableReset->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    TableReset->setPopupMode(QToolButton::InstantPopup);
    connect(TableReset, SIGNAL(clicked()), parent, SLOT(TableReset()));

    QToolButton *TextAlignment = new QToolButton(ToolBar);
    TextAlignment->setText("Text Align");
    TextAlignment->setIcon(QIcon("../OOPPROJECT/icons/TextSettings.png"));
    TextAlignment->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    TextAlignment->setPopupMode(QToolButton::InstantPopup);
    QAction *LeftAlign = new QAction("Align left",TextAlignment);
    LeftAlign->setIcon(QIcon("../OOPPROJECT/icons/LeftAlign.png"));
    QAction *CenterAlign = new QAction("Align center",TextAlignment);
    CenterAlign->setIcon(QIcon("../OOPPROJECT/icons/CenterAlign.png"));
    QAction *RightAlign = new QAction("Align right",TextAlignment);
    RightAlign->setIcon(QIcon("../OOPPROJECT/icons/RightAlign.png"));
    TextAlignment->addAction(LeftAlign);
    TextAlignment->addAction(CenterAlign);
    TextAlignment->addAction(RightAlign);
    connect(LeftAlign, SIGNAL(triggered()), parent, SLOT(LeftAlign()));
    connect(CenterAlign, SIGNAL(triggered()), parent, SLOT(CenterAlign()));
    connect(RightAlign, SIGNAL(triggered()), parent, SLOT(RightAlign()));

    _TxtDim = new QSpinBox(ToolBar);
    _TxtDim->setValue(10);
    connect(_TxtDim, SIGNAL(valueChanged(int)), parent, SLOT(SetTextSize()));

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
    TextAlignment->setMinimumWidth(110);
    TextAlignment->setStyleSheet("margin:5px;");
    _TxtDim->setMinimumWidth(110);
    _TxtDim->setStyleSheet("margin:5px;");


    QWidget *FileW = new QWidget();

    QHBoxLayout *FileL = new QHBoxLayout;
    FileL->setSpacing(0);


    QTabWidget *ChartList = new QTabWidget(this);
    ChartList->setTabPosition(QTabWidget::West);
    ChartList->addTab(new ChartSelection(parent), QString(""));
    ChartList->setTabIcon(0, QIcon("../OOPPROJECT/icons/NewGraph.png"));
    ChartList->setTabsClosable(true);

    QTableWidget *ValueTab = new QTableWidget(50, 50, this);

    FileL->addWidget(ValueTab);
    FileL->addWidget(ChartList);

    FileW->setLayout(FileL);

    _Files->addTab(FileW, QString("Untitled"));

    _Files->setTabsClosable(true);

    connect(_Files, SIGNAL(tabCloseRequested(int)), parent, SLOT(TabClose(int)));
    connect(static_cast<QTableWidget*>(_Files->widget(0)->layout()->itemAt(0)->widget()), SIGNAL(itemSelectionChanged()), parent, SLOT(SpinBox()));
    connect(static_cast<QTableWidget*>(_Files->widget(0)->layout()->itemAt(0)->widget()), SIGNAL(cellChanged(int,int)), parent, SLOT(ChartRefresh(int,int)));


    setCentralWidget(_Files);
    this->layout()->setSpacing(0);

    ToolBar->addWidget(NewRow);
    ToolBar->addWidget(NewColumn);
    ToolBar->addSeparator();
    ToolBar->addWidget(Clear);
    ToolBar->addWidget(Delete);
    ToolBar->addWidget(TableReset);
    ToolBar->addSeparator();
    ToolBar->addWidget(TextAlignment);
    ToolBar->addWidget(_TxtDim);
    addToolBar(Qt::LeftToolBarArea, ToolBar);

    connect(this, SIGNAL(closing()), parent, SLOT(mainWindowCloseEvent()));
}

void MainWindow::addRow(Flags dir)
{
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    switch (dir) {
        case (Flags::TOP):
            currentTable->insertRow(currentTable->currentRow());
        break;
        case (Flags::DOWN):
            currentTable->insertRow(currentTable->currentRow()+1);
        break;
        default:
        break;
    }
}

void MainWindow::addColumn(Flags dir){
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    switch (dir) {
        case (Flags::LEFT):
            currentTable->insertColumn(currentTable->currentColumn()+1);
        break;
        case (Flags::RIGHT):
            currentTable->insertColumn(currentTable->currentColumn());
        break;
        default:
        break;
    }
}

void MainWindow::clearTable(){
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    currentTable->clearContents();
}

void MainWindow::clearContent(Flags Content){
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    switch (Content) {
        case (Flags::SELECTION): {
            QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
            for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
                QTableWidgetItem *element = *it;
                element->setText("");
            }
        }
            break;

        case (Flags::COLUMN):{
            //TODO:Multiple columns selection
            int currentIndex = currentTable->currentColumn();
            for(int i=0; i<currentTable->rowCount(); i++){
                QTableWidgetItem *TI = currentTable->item(i, currentIndex);
                if(TI) TI->setText("");
            }
        }
            break;

        case (Flags::ROW):{
            //TODO:Multiple rows selection
            int currentIndex = currentTable->currentRow();
            for(int i=0; i<currentTable->columnCount(); i++){
                QTableWidgetItem *TI = currentTable->item(currentIndex, i);
                if(TI) TI->setText("");
            }
        }
            break;

        case (Flags::ALL):
            currentTable->clear();
            break;

        default:
            break;
    }
}

void MainWindow::deleteContent(Flags Content){
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    switch (Content) {
        case (Flags::COLUMN):
            //TODO:Multiple columns selection handle
            currentTable->removeColumn(currentTable->currentColumn());
            break;
        case (Flags::ROW):
            //TODO:Multiple row selection handle
            currentTable->removeRow(currentTable->currentRow());
            break;
        default:
            break;
    }
}

void MainWindow::textAlign(Flags dir){
    QTableWidget* currentTable = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex()));
    QList<QTableWidgetItem*> ItemList = currentTable->selectedItems();
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

void MainWindow::setSpinBox(int value){
    _TxtDim->setValue(value);
}

void MainWindow::setTextSize(int pointSize){
    QFont TFont= _Files->widget(_Files->currentIndex())->layout()->itemAt(0)->widget()->font();
    TFont.setPointSize(pointSize);
    QList<QTableWidgetItem*> ItemList = static_cast<QTableWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(0)->widget())->selectedItems();
    for (auto it = ItemList.begin(); it!=ItemList.end(); it++){
        QTableWidgetItem *element = *it;
        element->setFont(TFont);
    }
}

int MainWindow::getSpinValue(){
    return _TxtDim->value();
}


int MainWindow::getCurrentTabIndex(){
    return _Files->currentIndex();
}

QString MainWindow::getTabName(int index){
    if(index<0) return _Files->tabText(_Files->currentIndex());
    else return _Files->tabText(index);
}

QTableWidget* MainWindow::getFullTable(int index){
    return static_cast<QTableWidget*>(_Files->widget(index)->layout()->itemAt(0)->widget());
}

int MainWindow::getCurrentChartTabIndex(){
    return (static_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget())->currentIndex());
}

int MainWindow::getChartNumber(int index){
    return static_cast<QTabWidget*>(_Files->widget(index)->layout()->itemAt(1)->widget())->count();
}

ChartSettings* MainWindow::getChartTab(int index){
    //Ritorna la tab di indice index della sezione tab della current tab di Files
    return static_cast<ChartSettings*>(static_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget())->widget(index));
}

int MainWindow::getFilePosition(QString fileName){
    for (int i=0; i<_Files->count(); i++ ){
        if(_Files->tabText(i) == fileName){
            _Files->setCurrentIndex(i);
            return i;
        }
    }
    return -1;
}

void MainWindow::setCurrentTabTitle(QString fileName){
    _Files->setTabText(_Files->currentIndex(), fileName);
}

void MainWindow::closeTab(int index){
    _Files->removeTab(index);
}


void MainWindow::openFile(QString TabName, QTableWidget* Table){
    _Files->addTab(Table, TabName);
    _Files->setCurrentIndex(_Files->count()-1);
    connect(static_cast<QTableWidget*>(_Files->widget(_Files->count()-1)), SIGNAL(itemSelectionChanged()), parent(), SLOT(SpinBox()));
}

void MainWindow::chartTypeSelected(Flags type){
    switch(type){
        case(Flags::CANDLESTICK):{
            if(QTabWidget *ChartListCurrentIndex = dynamic_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget())){
                qDebug() << "CandleStick opened";
                ChartListCurrentIndex->insertTab(0, new CandleStickSettings(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget()), QIcon("../OOPPROJECT/icons/NewGraph.png"), QString(""));
                ChartListCurrentIndex->setCurrentIndex(0);
            }
            else{
                //errore run-time
            }
        }
            break;
        case(Flags::AREA) : case(Flags::LINES): case(Flags::PIE):{
            if(QTabWidget *ChartListCurrentIndex = dynamic_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget())){
//                QTabWidget *ChartListCurrentIndex = static_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget());
                ChartListCurrentIndex->insertTab(0, new AreaLinePieSettings(type, _Files->widget(1)),QIcon("../OOPPROJECT/icons/NewGraph.png"), QString(""));//TODO Settare il parent per i connect adeguatamente
                ChartListCurrentIndex->setCurrentIndex(0);
            }
        }
            break;
        case(Flags::BARS):{
            if(QTabWidget *ChartListCurrentIndex = dynamic_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget())){
//                QTabWidget *ChartListCurrentIndex = static_cast<QTabWidget*>(_Files->widget(_Files->currentIndex())->layout()->itemAt(1)->widget());
                ChartListCurrentIndex->insertTab(0, new BarSettings(_Files),QIcon("../OOPPROJECT/icons/NewGraph.png"), QString(""));//TODO Settare il parent per i connect adeguatamente
                ChartListCurrentIndex->setCurrentIndex(0);
            }
        }
            break;
        default:
            break;
    }
}

void MainWindow::newTab(){
    _Files->addTab(new QTableWidget(50,50), QString("Untitled"));
    _Files->setCurrentIndex(_Files->count()-1);
    connect(static_cast<QTableWidget*>(_Files->widget(_Files->count()-1)), SIGNAL(itemSelectionChanged()), parent(), SLOT(SpinBox()));
}

void MainWindow::closeEvent(QCloseEvent *){
   emit closing();
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

