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
    QMessageBox::StandardButton ret ;
    ret = QMessageBox::question(NULL,"server or client","as server");
    bool server = false ;
    if(ret == QMessageBox::Yes){
        server = true ;
    }
    MultiGame board;
    board.show();
    return a.exec();
}
