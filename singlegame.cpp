#include "singlegame.h"
#include <QBoxLayout>
#include <QPushButton>
#include <numeric>
#include <QTimer>
#include <iostream>
#include <QPainter>
#include <algorithm>
#include <random>

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
      QTimer::singleShot(100, this, SLOT(computerMove()));
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
        }
      };
      drawStone(m_lastMove->_moveid);
    }

}
void SingleGame::computerMove(){
  if (whoWinTheGame()) return;
  if (m_lastMove)
  {
    delete m_lastMove;
    m_lastMove = nullptr;
  }
    m_lastMove = this->getBestMove();
    if (!m_lastMove) return;
    this->moveStone(m_lastMove->_moveid, m_lastMove->_killid, m_lastMove->_rowTo, m_lastMove->_colTo);
    this->restartGame();
    selected = -1;
    update();
}

void SingleGame::saveAllPossibleMove(int moveid, int killid, int row, int col, QVector<Step *>& steps){
    Step* step = new Step;
    step->_colFrom = stone[moveid].getCol();
    step->_colTo = col;
    step->_rowFrom = stone[moveid].getRow();
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;
    steps.push_back(step);
}
void SingleGame::getALLPossibleMove(QVector<Step *> & steps){
    if ((whoWinTheGame() == Stone::RED && !this->bRedTurn) ||
            (whoWinTheGame() == Stone::BLACK && this->bRedTurn)) return;

    //id [16,31] is black
    int min = 16 ;
    int max = 32 ;
    if(this->bRedTurn){
         //id [0,15] is red
        min = 0 ;
        max = 16 ;
    }
    for(int i = min ; i < max ; i++){
        if(this->stone[i].getIsDead())continue;
        for(int row = 1 ; row <= 9 ; row ++){
            for(int col = 1 ; col <= 10 ; col ++){
                int killid = this->getStoneId(row *d,col*d);
                if(this->isRegularMovement(i,row*d,col*d,killid)){
                    this->saveAllPossibleMove(i,killid,row*d,col*d,steps);
                }
            }
        }
    }
}


int SingleGame::calScore(){
    //enum TYPE{JIANG,SHUAI,BING,ZU,REDPAO,BLACKPAO,REDCHE,BLACKCHE,REDMA,BLACKMA,BLACKXIANG,REDXIANG,REDSHI,BLACKSHI};
  int pao = 699;//pao will not eat ma if pao >= ma + zu when level = 4
  int ma = 499;
    static int chessScore[] = {150000,150000,200,200,pao,pao,1000,1000,499,499,100,100,100,100};
    int redScore = 0 ;
    int blackScore = 0 ;

    for(int i = 0 ; i < 16 ; i++){
        if(!this->stone[i].getIsDead()){
            redScore += chessScore[this->stone[i].type];
        }
    }

    for(int i = 16 ; i < 32 ; i++){
        if(!this->stone[i].getIsDead()){
            blackScore += chessScore[this->stone[i].type];
        }
    }
    return (blackScore - redScore) ;
}
int SingleGame::getMinScore(int level , int curMaxScore){

    if(!bRedTurn) throw(-1);
    if(level == 0) return this->calScore();

    QVector<Step*>steps ;
    //1.get all possible move steps
    this->getALLPossibleMove(steps);
    int minScore = std::numeric_limits<int>::max();
    while (steps.count()) {
        Step * step = steps.back() ;
        steps.removeLast();

        fakeMove(step);

        //3.assess each step
        int score = getMaxScore(level-1,minScore);
        unfakeMove(step);

        delete step;
        if(score <= curMaxScore){
             while (steps.count()) {
                 Step * step = steps.back() ;
                 steps.removeLast();
                 delete step ;
             }
            return score;
        }
        if(score < minScore){
            minScore = score ;
        }

    }
    return minScore;
}

int SingleGame::getMaxScore(int level,int curMinScore){

    if(bRedTurn) throw(-1);
    if(level == 0) return this->calScore();

    QVector<Step*>steps ;
    //1.get all possible move steps
    this->getALLPossibleMove(steps);
    int maxScore = std::numeric_limits<int>::min();

//    if (level == 1)
//    {
//        std::cerr<<"black should live!\n";
//    }
//    else if (level == 3)
//    {
//        std::cerr<<"black should move jiang!\n";
//        std::cerr<<"and black sh live!\n";
//    }
    while (steps.count()) {
        Step * step = steps.back() ;
        steps.removeLast();

        fakeMove(step);
        //3.assess each step
        int score = getMinScore(level-1,maxScore);
        unfakeMove(step);
        delete step ;

        if(score >= curMinScore){//can not both contain ==
            while (steps.count()) {
                Step * step = steps.back() ;
                steps.removeLast();
                delete step ;
            }
            if (level == 3)
                return score;
            else
                return score;
            return score;
        }
        if(score > maxScore){
            maxScore = score ;
        }

    }
    if (level == 3)
        return maxScore;
    else
        return maxScore;
}

Step* SingleGame::getBestMove(){
    if (bRedTurn) throw(-1);
    //computer move
    QVector<Step*>steps ;
    //1.get all possible move steps
    this->getALLPossibleMove(steps);
    {
      std::vector<Step*> stlsteps;
      for (auto step : steps) stlsteps.push_back(step);

      auto rng = std::default_random_engine {};
      std::shuffle(std::begin(stlsteps), std::end(stlsteps), rng);
      steps.clear();
      for (auto step : stlsteps) steps.push_back(step);

    }

    //2.try to move
    int maxScore = std::numeric_limits<int>::min();
    Step * realstp = NULL;
    while (steps.count()) {
        Step * step = steps.back() ;
        steps.removeLast();

        fakeMove(step);
        int score = this->getMinScore(level-1,maxScore);
        unfakeMove(step);

        if(!(score < maxScore)){
            maxScore = score ;
            if(realstp != NULL) delete realstp;
            realstp = step ;
        }else{
            delete step ;
        }
    }
    //get best move step
    std::cerr<<"Blk can get max of "<<maxScore<<std::endl;
    return realstp ;
}

Step *SingleGame::getBestRedMove()
{
    if (!bRedTurn) throw(-1);

  //computer move
  QVector<Step*>steps ;
  //1.get all possible move steps
  this->getALLPossibleMove(steps);
  if (1){
    std::vector<Step*> stlsteps;
    for (auto step : steps) stlsteps.push_back(step);

    auto rng = std::default_random_engine {};
    std::shuffle(std::begin(stlsteps), std::end(stlsteps), rng);
    steps.clear();
    for (auto step : stlsteps) steps.push_back(step);

  }

  //2.try to move
  int minScore = std::numeric_limits<int>::max();
  Step * realstp = NULL;
  while (steps.count()) {
      Step * step = steps.back() ;
      steps.removeLast();

      fakeMove(step);
      int score = this->getMaxScore(level-1,minScore);//because here will
      //return minScore
      unfakeMove(step);

      if(score <= minScore){//why this is wrong
          minScore = score ;
          if(realstp != NULL) delete realstp;
          realstp = step ;
      }else{
          delete step ;
      }
  }
  //get best move step
  std::cerr<<"Red can get min of "<<minScore<<std::endl;
  return realstp ;
}

void SingleGame::back(){
    backOne();
    backOne();
}
