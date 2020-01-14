#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include <QObject>
#include "chessplayer.h"

class humanPlayer : public chessPlayer
{
  Q_OBJECT
public:
  humanPlayer(Board* board, Stone::COLOR color);
  virtual void acceptTurn() override;
};

#endif // HUMANPLAYER_H
