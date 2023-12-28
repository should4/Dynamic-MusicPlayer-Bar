#include "widget.h"
#include "dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    Widget w;
//    w.show();

    Dialog dlg;
    dlg.show();
    return a.exec();
}
