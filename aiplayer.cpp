#include "aiplayer.h"
#include <assert.h>
#include <iostream>
#include <random>

aiPlayer::aiPlayer(Board *board, Stone::COLOR color)
  : chessPlayer(board, color)
{

}

void aiPlayer::acceptTurn()
{
  assert(m_board->bRedTurn == (m_color == Stone::RED));
  if (m_color == Stone::RED)
  {
    emit move(getBestRedMove());
  }
  else
  {
    emit move(getBestBlackMove());
  }
}

std::shared_ptr<Step> aiPlayer::getBestBlackMove()
{
  //computer move
  QVector<std::shared_ptr<Step>>steps ;
  //1.get all possible move steps
  m_board->getALLPossibleMove(steps);
  {
    std::vector<std::shared_ptr<Step>> stlsteps;
    for (auto step : steps) stlsteps.push_back(step);

    unsigned seed;// = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine {seed};
    std::shuffle(std::begin(stlsteps), std::end(stlsteps), rng);
    steps.clear();
    for (auto step : stlsteps) steps.push_back(step);

  }

  //2.try to move
  std::pair<int, int> maxScore = {std::numeric_limits<int>::min(), -2};
  std::shared_ptr<Step> realstp = NULL;
  while (steps.count()) {
      std::shared_ptr<Step> step = steps.back() ;
      steps.removeLast();

//      if (isDumplicateStep(step)) continue;
      m_board->fakeMove(step);
      auto score = this->getMinScore(level-1,maxScore.first);
      m_board->unfakeMove(step);

      if(score.first > maxScore.first ||
         (score.first == maxScore.first && score.second > maxScore.second)){
          maxScore = score ;
          realstp = step ;
      }
  }
  //get best move step
  std::cerr<<"Blk can get max of "<<maxScore.first<<std::endl;
  return realstp ;
}

std::pair<int, int> aiPlayer::calScore(){
    //enum TYPE{JIANG,SHUAI,BING,ZU,REDPAO,BLACKPAO,REDCHE,BLACKCHE,REDMA,BLACKMA,BLACKXIANG,REDXIANG,REDSHI,BLACKSHI};
  int pao = 699;//pao will not eat ma if pao >= ma + zu when level = 4
  int ma = 499;
    static int chessScore[] = {150000,150000,200,200,pao,pao,1000,1000,499,499,100,100,100,100};
    int redScore = 0 ;
    int blackScore = 0 ;

    for(int i = 0 ; i < 16 ; i++){
        if(!m_board->stone[i].getIsDead()){
            redScore += chessScore[m_board->stone[i].type];
        }
    }

    for(int i = 16 ; i < 32 ; i++){
        if(!m_board->stone[i].getIsDead()){
            blackScore += chessScore[m_board->stone[i].type];
        }
    }
    return {(blackScore - redScore), 0};
}
std::pair<int, int> aiPlayer::getMinScore(int level , int curMaxScore){

    if(!m_board->bRedTurn) throw(-1);
    if(level == 0) return this->calScore();

    QVector<std::shared_ptr<Step>>steps ;
    //1.get all possible move steps
    m_board->getALLPossibleMove(steps);
    std::pair<int, int> minScore = {std::numeric_limits<int>::max(), level};
    while (steps.count()) {
        std::shared_ptr<Step> step = steps.back() ;
        steps.removeLast();

        m_board->fakeMove(step);

        //3.assess each step
        std::pair<int, int> score = getMaxScore(level-1,minScore.first);
        m_board->unfakeMove(step);

        if(score.first <= curMaxScore){
             while (steps.count()) {
                 std::shared_ptr<Step> step = steps.back() ;
                 steps.removeLast();
             }
             return {std::max(score.first, INT_MIN+1) -1, -1};
        }
        if(score.first < minScore.first){
            minScore = score ;
        }

    }
    return minScore;
}

std::pair<int, int> aiPlayer::getMaxScore(int level,int curMinScore){

    if(m_board->bRedTurn) throw(-1);
    if(level == 0) return this->calScore();

    QVector<std::shared_ptr<Step>>steps ;
    //1.get all possible move steps
    m_board->getALLPossibleMove(steps);
    std::pair<int, int> maxScore = {std::numeric_limits<int>::min(),level};

    while (steps.count()) {
        std::shared_ptr<Step> step = steps.back() ;
        steps.removeLast();

        m_board->fakeMove(step);
        //3.assess each step
        std::pair<int, int> score = getMinScore(level-1,maxScore.first);
        m_board->unfakeMove(step);

        if(score.first >= curMinScore){//can not both contain ==?
            while (steps.count()) {
                std::shared_ptr<Step> step = steps.back() ;
                steps.removeLast();
            }
            if (level == 3)
              return {std::min(score.first, INT_MAX-1)+1, -1};
            else
                return {std::min(score.first, INT_MAX-1)+1, -1};
            return score;
        }
        if(score.first > maxScore.first){
            maxScore = score ;
        }

    }
    if (level == 3)
        return maxScore;
    else
      return maxScore;
}

std::shared_ptr<Step> aiPlayer::getBestRedMove()
{
  //computer move
  QVector<std::shared_ptr<Step>>steps ;
  //1.get all possible move steps
  m_board->getALLPossibleMove(steps);
  if (1){
    std::vector<std::shared_ptr<Step>> stlsteps;
    for (auto step : steps) stlsteps.push_back(step);

    unsigned seed;// = std::chrono::system_clock::now().time_since_epoch().count();
    auto rng = std::default_random_engine {seed};
    std::shuffle(std::begin(stlsteps), std::end(stlsteps), rng);
    steps.clear();
    for (auto step : stlsteps) steps.push_back(step);

  }

  //2.try to move
  std::pair<int, int> minScore = {std::numeric_limits<int>::max(), -2};
  std::shared_ptr<Step> realstp = NULL;
  while (steps.count()) {
      std::shared_ptr<Step> step = steps.back() ;
      steps.removeLast();

//      if (isDumplicateStep(step)) continue;

      m_board->fakeMove(step);
      auto score = this->getMaxScore(level-1,minScore.first);//because here will
      //return minScore
      m_board->unfakeMove(step);

      if(score.first < minScore.first ||
         (score.first == minScore.first && score.second > minScore.second)){
          minScore = score ;
          realstp = step ;
      }
  }
  //get best move step
  std::cerr<<"Red can get min of "<<minScore.first<<std::endl;
  return realstp ;
}

