#include "singlegame.h"
#include <QBoxLayout>
#include <QPushButton>
#include <numeric>
#include <QTimer>
#include <iostream>
#include <QPainter>
#include <algorithm>
#include <random>
#include <chrono>       // std::chrono::system_clock

SingleGame::SingleGame(QWidget *parent) : Board(parent){
    this->level = 4 ;
}
SingleGame::~SingleGame(){

}

void SingleGame::click(int id, int row, int col){
    if(!this->bRedTurn){
        return ;
    }
    Board::click(id,row,col);

    if(!this->bRedTurn)
      QTimer::singleShot(100, this, SLOT(computerBlackMove()));
}

void SingleGame::paintEvent(QPaintEvent *e)
{
    Board::paintEvent(e);
    //draw last move
    if (m_lastMove){
      auto drawStone =[this](int id){
        QPainter pen(this);
        if(!stone[id].getIsDead()){

          pen.setBrush(Qt::gray);
          QFont serifFont("Times", 20, QFont::Bold);
          pen.setFont(serifFont);
          if(stone[id].color == Stone::RED){
            pen.setPen(Qt::red);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2,d/2);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-1,d/2-1);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-2,d/2-2);
            pen.drawText(QRectF(stone[id].getRow()-20,stone[id].getCol()-20,40,40),Qt::AlignCenter,stone[id].getSoneName());
          }else{
            pen.setPen(Qt::black);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2,d/2);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-1,d/2-1);
            pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-2,d/2-2);
            pen.drawText(QRectF(stone[id].getRow()-20,stone[id].getCol()-20,40,40),Qt::AlignCenter,stone[id].getSoneName());
          }

          {

            pen.setPen(Qt::lightGray);
            pen.setBrush(Qt::lightGray);
            pen.drawEllipse(QPoint(m_lastMove->_rowFrom, m_lastMove->_colFrom),d/2,d/2);
  //          pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-1,d/2-1);
  //          pen.drawEllipse(QPoint(stone[id].getRow(),stone[id].getCol()),d/2-2,d/2-2);
//            pen.drawText(QRectF(m_lastMove->_rowFrom-20,m_lastMove->_colFrom-20,40,40),Qt::AlignCenter,stone[id].getSoneName());
          }
        }
      };
      drawStone(m_lastMove->_moveid);
    }

}
void SingleGame::computerBlackMove(){
  if (whoWinTheGame()) return;

    m_lastMove;// = this->getBestBlackMove();
    if (!m_lastMove) return;
    lastBlackMove.push_back(m_lastMove);
    this->moveStone(m_lastMove->_moveid, m_lastMove->_killid, m_lastMove->_rowTo, m_lastMove->_colTo);
    this->restartGame();
    selected = -1;
    update();
}





bool SingleGame::isDumplicateStep(std::shared_ptr<Step> step)
{
  if (bRedTurn)
  {
    if (lastRedMove.size() >= 2 && *step == *lastRedMove[lastRedMove.size() - 2]) return true;
    else return false;
  }
  else
  {
    if (lastBlackMove.size() >= 2 && *step == *lastBlackMove[lastBlackMove.size() - 2]) return true;
    else return false;
  }
}


void SingleGame::back(){
    backOne();
    backOne();
}
