#ifndef ZEROGAME_H
#define ZEROGAME_H
#include "singlegame.h"

class ZeroGame : public SingleGame
{
  Q_OBJECT
public:
  explicit ZeroGame(QWidget *parent = 0);
  void start();
  void computerMoveStart();
  void computerRedMove();
  void computerOneMove();

};

#endif // ZEROGAME_H
