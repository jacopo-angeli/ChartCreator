#include "controller.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller* program = new Controller();

    return a.exec();
}
