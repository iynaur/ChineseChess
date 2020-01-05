#include <QApplication>
#include"board.h"
#include "multigame.h"
#include "singlegame.h"
#include "netgame.h"
#include <QMessageBox>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //MultiGame board;
    //Board board;
    //SingleGame board ;

    MultiGame board;
    board.show();
    return a.exec();
}
