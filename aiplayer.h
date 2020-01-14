#ifndef AIPLAYER_H
#define AIPLAYER_H

#include "chessplayer.h"

class aiPlayer : public chessPlayer
{
  Q_OBJECT
public:
  aiPlayer(Board* board, Stone::COLOR color);
  virtual void acceptTurn() override;
  std::pair<int, int> calScore();
  std::pair<int, int> getMinScore(int level, int curMaxScore);
  std::pair<int, int> getMaxScore(int level, int curMinScore);
protected:
  std::shared_ptr<Step> getBestBlackMove();
  std::shared_ptr<Step> getBestRedMove();
  int level = 4;
};

#endif // AIPLAYER_H
