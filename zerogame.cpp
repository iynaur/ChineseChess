#include "zerogame.h"
#include <QTimer>
#include <iostream>

ZeroGame::ZeroGame(QWidget *parent) : SingleGame(parent)
{

}

void ZeroGame::start()
{
  QTimer::singleShot(100, this, &ZeroGame::computerMoveStart);
}

void ZeroGame::computerMoveStart()
{
  computerOneMove();
  QTimer::singleShot(2, this, &ZeroGame::computerMoveStart);
}

void ZeroGame::computerOneMove()
{
  int msec = 1;
  if (bool normal = true){
//    QTimer::singleShot(msec, this, &ZeroGame::computerRedMove);
//    QTimer::singleShot(2*msec, this, &ZeroGame::computerMove);
      if (bRedTurn)computerRedMove();
      else computerMove();
      std::cerr<<"cur score is "<<calScore()<<std::endl;
  }
  else {
    QTimer::singleShot(msec, this, &ZeroGame::computerMove);
    QTimer::singleShot(2*msec, this, &ZeroGame::computerRedMove);
  }
}

void ZeroGame::computerRedMove(){
  if (whoWinTheGame()) return;
  if (m_lastMove)
  {
    delete m_lastMove;
    m_lastMove = nullptr;
  }
    m_lastMove = this->getBestRedMove();
    if (!m_lastMove) return;
    this->moveStone(m_lastMove->_moveid, m_lastMove->_killid, m_lastMove->_rowTo, m_lastMove->_colTo);
    this->restartGame();
    selected = -1;
    update();
}
