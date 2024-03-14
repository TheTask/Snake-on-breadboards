#include "game.h"


void game::game( char* lastButtonPressPtr )
{
  static unsigned long lastTime = 0;
  unsigned long currentTime = millis();
  bool update = currentTime - lastTime > 1000;

  //game::eventHandler( lastButtonPressPrt );


  switch( game::_currentGameState ) 
  {
    case game::gameState::INIT:
      if( update )
      {
        leds::init();
        game::_currentGameState = game::gameState::SELECT_DIFFICULTY;
      } 
      break;

    case game::gameState::SELECT_DIFFICULTY:
      if( update )
      {
        leds::displayConfigScene();

        if( game::_hasDifficultyBeenSet )
        {
          game::_currentGameState = game::gameState::STARTUP_SEQUENCE;
          flags::canProcessInput = false;
        }
      }
      break;

    case game::gameState::STARTUP_SEQUENCE:
      if( update )
      {
        if( !sequence::isStartupSequenceDone ) sequence::startupSequence();
        else
        {
          snake::initBoard();
          snake::initSnake();
          snake::initFood();
          game::_currentGameState = game::gameState::GAME;
        }
      }
      break;

    case game::gameState::GAME:
      update = currentTime - lastTime >= config::getGameConfig().UPDATE_DELAY;

      if( update ) 
      {
        lastTime = currentTime;
        
        snake::move();

        if( snake::hasGameEnded() ) game::_currentGameState = game::gameState::ENDING_SEQUENCE;
        else leds::display( snake::board );
      }

      if( *lastButtonPressPtr != 0 ) 
      {
        snake::enqueueDirection( String( *lastButtonPressPtr ) );
        *lastButtonPressPtr = 0;
      }
      break;
    case game::gameState::ENDING_SEQUENCE:
      if( snake::hasWon() ) sequence::gamewonSequence();
      if( snake::hasLost() ) sequence::gameoverSequence();

      softwareReset();
      break;
    case game::gameState::JOYSTICK_NOT_CONNECTED:
      leds::displayColor( colors::BLUE );
      delay(10000);
      break;
  }
}