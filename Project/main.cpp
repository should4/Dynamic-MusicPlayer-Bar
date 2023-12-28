#include "SartWidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    SartWidget w;
    w.show();
    return a.exec();
}
