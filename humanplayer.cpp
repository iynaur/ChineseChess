#include "humanplayer.h"
#include <assert.h>
#include <iostream>

humanPlayer::humanPlayer(Board* board, Stone::COLOR color)
 : chessPlayer(board, color)
{

}

void humanPlayer::acceptTurn()
{
  assert(m_board->bRedTurn == (m_color == Stone::RED));
}
