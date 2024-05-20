#include "game.h"

void game::_eventHandler( char* lastButtonPressPtr )
{
  if( *lastButtonPressPtr != 0 ) 
  {
    String buttonPressed = String( *lastButtonPressPtr );

    if( buttonPressed == "F" )
    {
      flags::isJoystickConnected = false;
      game::_currentGameState = game::gameState::JOYSTICK_NOT_CONNECTED;
    }

    if( buttonPressed == "T" )
    {
      flags::isJoystickConnected = true;
      game::_currentGameState = game::gameState::INIT;
    }

    switch( game::_currentGameState ) 
    {
      case game::gameState::SELECT_DIFFICULTY:
        if( buttonPressed == "B"  || buttonPressed == "Y" || buttonPressed == "A" )
        { 
               if( buttonPressed == "B" ) config::setDifficulty( config::difficulty::EASY );
          else if( buttonPressed == "Y" ) config::setDifficulty( config::difficulty::MEDIUM );
          else if( buttonPressed == "A" ) config::setDifficulty( config::difficulty::HARD );

          game::_hasDifficultyBeenSet = true;
        }
        break;

      case game::gameState::GAME:
        snake::enqueueDirection( buttonPressed );
        break;
    }
    *lastButtonPressPtr = 0;
  }
}

void game::game( char* lastButtonPressPtr )
{
  unsigned long currentTime = millis();
  bool update = currentTime - game::_lastTime >= config::getGameConfig().UPDATE_DELAY;

  switch( game::_currentGameState ) 
  {
    case game::gameState::INIT:
      leds::init();
      flags::canProcessInput = true; 
      game::_currentGameState = game::gameState::SELECT_DIFFICULTY;
      break;

    case game::gameState::SELECT_DIFFICULTY:
      leds::displayConfigScene();

      if( game::_hasDifficultyBeenSet )
      {
        game::_currentGameState = game::gameState::STARTUP_SEQUENCE;
        flags::canProcessInput = false;
      }
      break;

    case game::gameState::STARTUP_SEQUENCE:
      if( !sequence::isStartupSequenceDone ) sequence::startupSequence();
      else
      {
        snake::initBoard();
        snake::initSnake();
        snake::initFood();

        game::_currentGameState = game::gameState::GAME;
      }
    
    break;

    case game::gameState::GAME:
      if( update ) 
      {
        game::_lastTime = currentTime;
  
        snake::move();
        leds::displayBoard( snake::board,snake::linearSnakeHeadIndex );
        leds::sevenSegmentDisplayWrite( snake::snakeVec.size() - config::INIT_SNAKE_LENGTH );

        if( snake::hasGameEnded() ) 
        {
          game::_currentGameState = game::gameState::ENDING_SEQUENCE;
          delay( sequence::_halfSecondDelay );
        }
      }
      break;

    case game::gameState::ENDING_SEQUENCE:
      if( snake::hasWon() ) sequence::gamewonSequence();
      else sequence::gameoverSequence();

      softwareReset();

    case game::gameState::JOYSTICK_NOT_CONNECTED:
      leds::displayColor( colors::BLUE );
      break;
  }
  game::_eventHandler( lastButtonPressPtr );
}