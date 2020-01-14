#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include <QObject>
#include "board.h"
#include "step.h"
#include "stone.h"

class chessPlayer : public QObject
{
  Q_OBJECT
public:
  chessPlayer(Board* board, Stone::COLOR color);
  virtual void acceptTurn() = 0;

signals:
  void move(std::shared_ptr<Step> step);
protected:
  Board* m_board;
  Stone::COLOR m_color;
};

#endif // CHESSPLAYER_H
