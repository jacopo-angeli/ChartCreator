#include "chartsettings.h"
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QWidgetAction>
#include <QStringList>
#include <QColorDialog>
#include <QtCharts>
#include <QWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
ChartSettings::ChartSettings(QWidget * parent) : QWidget(parent)
{
    _ValueTab= new QTableWidget(50,50);
    _ValueTab->setFixedHeight(250);

    QVBoxLayout* vert= new QVBoxLayout();
    vert->addWidget(_ValueTab);
//layout orizzontale
    QHBoxLayout * hor1=new QHBoxLayout();
    QHBoxLayout * hor2=new QHBoxLayout();
    QHBoxLayout * hor3=new QHBoxLayout();
    QHBoxLayout * hor4=new QHBoxLayout();
    QHBoxLayout * hor5=new QHBoxLayout();
    QHBoxLayout * hor6=new QHBoxLayout();
    QHBoxLayout * hor7=new QHBoxLayout();
    QHBoxLayout * hor8=new QHBoxLayout();
    QHBoxLayout * hor9=new QHBoxLayout();
    QHBoxLayout * hor10=new QHBoxLayout();
    QHBoxLayout * foot=new QHBoxLayout();
//labels
    QLabel* _lab1=new  QLabel("Title");
    _lab1->setMaximumHeight(50);
    _lab1->setMaximumWidth(250);

    QLabel* _lab2=new  QLabel("Description");
    _lab2->setMaximumHeight(50);
    _lab2->setMaximumWidth(250);

    QLabel* _lab3=new  QLabel("Data Series");
    _lab3->setMaximumHeight(50);
    _lab3->setMaximumWidth(250);

    QLabel* _lab4=new  QLabel("Opening Prices");
    _lab4->setMaximumHeight(50);
    _lab4->setMaximumWidth(250);

    QLabel* _lab5=new  QLabel("Closing Prices");
    _lab5->setMaximumHeight(50);
    _lab5->setMaximumWidth(250);

    QLabel* _lab6=new  QLabel("Bottom Prices");
    _lab6->setMaximumHeight(50);
    _lab6->setMaximumWidth(250);

    QLabel* _lab7=new  QLabel("Lowest Prices");
    _lab7->setMaximumHeight(50);
    _lab7->setMaximumWidth(250);

    QLabel* _lab8=new  QLabel("Highest Prices");
    _lab8->setMaximumHeight(50);
    _lab8->setMaximumWidth(250);

    QLabel* _lab9=new  QLabel("Categories");
    _lab9->setMaximumHeight(50);
    _lab9->setMaximumWidth(250);

    QLabel* _lab10=new  QLabel("COlor Palette");
    _lab10->setMaximumHeight(50);
    _lab10->setMaximumWidth(250);

//buttons

    QPushButton* _btn1=new QPushButton("PICK");
    _btn1->setMaximumHeight(50);
    _btn1->setMaximumWidth(250);

    QPushButton* _btn2=new QPushButton("PICK");
    _btn2->setMaximumHeight(50);
    _btn2->setMaximumWidth(250);

    QPushButton* _btn3=new QPushButton("PICK");
    _btn3->setMaximumHeight(50);
    _btn3->setMaximumWidth(250);

    QPushButton* _btn4=new QPushButton("PICK");
    _btn4->setMaximumHeight(50);
    _btn4->setMaximumWidth(250);

    QPushButton* _btn5=new QPushButton("PICK");
    _btn5->setMaximumHeight(50);
    _btn5->setMaximumWidth(250);

    QPushButton* _btn6=new QPushButton("PICK");
    _btn6->setMaximumHeight(50);
    _btn6->setMaximumWidth(250);

    QPushButton* _btn7=new QPushButton("PICK");
    _btn7->setMaximumHeight(50);
    _btn7->setMaximumWidth(250);

    QPushButton* _btn8=new QPushButton("PICK");
    _btn8->setMaximumHeight(50);
    _btn8->setMaximumWidth(250);

    QPushButton* _btn9=new QPushButton("PICK");
    _btn9->setMaximumHeight(50);
    _btn9->setMaximumWidth(250);

    QPushButton* _btn10=new QPushButton("PICK");
    _btn10->setMaximumHeight(50);
    _btn10->setMaximumWidth(250);

    QPushButton* _help=new QPushButton("HELP");
    _btn10->setMaximumHeight(25);
    _btn10->setMaximumWidth(200);

    QPushButton* _cancel=new QPushButton("CANCEL");
    _btn10->setMaximumHeight(25);
    _btn10->setMaximumWidth(200);

    QPushButton* _create=new QPushButton("CREATE");
    _btn10->setMaximumHeight(25);
    _btn10->setMaximumWidth(200);

//textboxes

    QTextEdit* _txt1=new QTextEdit("text");
    _txt1->setMaximumHeight(50);
    _txt1->setMaximumWidth(250);

    QTextEdit* _txt2=new QTextEdit("text");
    _txt2->setMaximumHeight(50);
    _txt2->setMaximumWidth(250);

    QTextEdit* _txt3=new QTextEdit("text");
    _txt3->setMaximumHeight(50);
    _txt3->setMaximumWidth(250);

    QTextEdit* _txt4=new QTextEdit("text");
    _txt4->setMaximumHeight(50);
    _txt4->setMaximumWidth(250);

    QTextEdit* _txt5=new QTextEdit("text");
    _txt5->setMaximumHeight(50);
    _txt5->setMaximumWidth(250);

    QTextEdit* _txt6=new QTextEdit("text");
    _txt6->setMaximumHeight(50);
    _txt6->setMaximumWidth(250);

    QTextEdit* _txt7=new QTextEdit("text");
    _txt7->setMaximumHeight(50);
    _txt7->setMaximumWidth(250);

    QTextEdit* _txt8=new QTextEdit("text");
    _txt8->setMaximumHeight(50);
    _txt8->setMaximumWidth(250);

    QTextEdit* _txt9=new QTextEdit("text");
    _txt9->setMaximumHeight(50);
    _txt9->setMaximumWidth(250);

//setting layout
    //line1
    hor1->addWidget(_lab1);
    hor1->addWidget(_btn1);
    hor1->addWidget(_txt1);
        vert->addLayout(hor1);
    //line2
    hor2->addWidget(_lab2);
    hor2->addWidget(_btn2);
    hor2->addWidget(_txt2);
        vert->addLayout(hor2);

    //line3
    hor3->addWidget(_lab3);
    hor3->addWidget(_btn3);
    hor3->addWidget(_txt3);
        vert->addLayout(hor3);
    //line4
    hor4->addWidget(_lab4);
    hor4->addWidget(_btn4);
    hor4->addWidget(_txt4);
        vert->addLayout(hor4);
    //line5
    hor5->addWidget(_lab5);
    hor5->addWidget(_btn5);
    hor5->addWidget(_txt5);
        vert->addLayout(hor5);
    //line6
    hor6->addWidget(_lab6);
    hor6->addWidget(_btn6);
    hor6->addWidget(_txt6);
        vert->addLayout(hor6);
    //line7
    hor7->addWidget(_lab7);
    hor7->addWidget(_btn7);
    hor7->addWidget(_txt7);
        vert->addLayout(hor7);
    //line8
    hor8->addWidget(_lab8);
    hor8->addWidget(_btn8);
    hor8->addWidget(_txt8);
        vert->addLayout(hor8);
    //line9
    hor9->addWidget(_lab9);
    hor9->addWidget(_btn9);
    hor9->addWidget(_txt9);
        vert->addLayout(hor9);
    //line10
    hor10->addWidget(_lab10);
    hor10->addWidget(_btn10);
        vert->addLayout(hor10);

    //footer
    foot->addWidget(_help);
    foot->addWidget(_cancel);
    foot->addWidget(_create);
    foot->setAlignment(Qt::AlignBottom | Qt::AlignRight);
        vert->addLayout(foot);

    setLayout(vert);
   setWindowFlag(Qt::MSWindowsFixedSizeDialogHint);
   setFixedSize(600,1000);

}
