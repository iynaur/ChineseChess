#include "mainwidget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;
    //MultiGame w ;
    w.show();
    return a.exec();
}
