#ifndef GAME_H
#define GAME_H

#include "config.h"
#include "leds.h"
#include "snake.h"
#include "sequences.h"
#include "flags.h"

void softwareReset();

namespace game
{
  enum gameState 
  {
    INIT,
    SELECT_DIFFICULTY,
    STARTUP_SEQUENCE,
    GAME,
    ENDING_SEQUENCE
  };

  inline gameState _currentGameState = gameState::INIT;

  static bool _hasDifficultyBeenSet = false;
  void game( char* lastButtonPress );
}

#endif