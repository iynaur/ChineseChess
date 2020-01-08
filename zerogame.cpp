#include "zerogame.h"
#include <QTimer>

ZeroGame::ZeroGame(QWidget *parent) : SingleGame(parent)
{

}

void ZeroGame::start()
{
  QTimer::singleShot(100, this, &ZeroGame::computerMoveStart);
}

void ZeroGame::computerMoveStart()
{
  int msec = 1;
  if (bool normal = true){
    QTimer::singleShot(msec, this, &ZeroGame::computerRedMove);
    QTimer::singleShot(2*msec, this, &ZeroGame::computerMove);
  }
  else {
    QTimer::singleShot(msec, this, &ZeroGame::computerMove);
    QTimer::singleShot(2*msec, this, &ZeroGame::computerRedMove);
  }
  QTimer::singleShot(2*msec, this, &ZeroGame::computerMoveStart);
}

void ZeroGame::computerRedMove(){
  if (m_lastMove)
  {
    delete m_lastMove;
    m_lastMove = nullptr;
  }
    m_lastMove = this->getBestRedMove();
    this->moveStone(m_lastMove->_moveid, m_lastMove->_killid, m_lastMove->_rowTo, m_lastMove->_colTo);
    this->restartGame();
    selected = -1;
    update();
}
