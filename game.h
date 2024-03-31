#ifndef GAME_H
#define GAME_H

#include "sequences.h"

void softwareReset();

namespace game
{
  enum gameState 
  {
    INIT,
    SELECT_DIFFICULTY,
    STARTUP_SEQUENCE,
    GAME,
    ENDING_SEQUENCE,
    JOYSTICK_NOT_CONNECTED
  };

  static unsigned long _lastTime = 0;
  static gameState _currentGameState = gameState::INIT;
  static bool _hasDifficultyBeenSet = false;
  
  void _eventHandler( char* lastButtonPressPtr );
  void game( char* lastButtonPressPtr );
}

#endif