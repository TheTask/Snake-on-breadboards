#include "game.h"


void game::game( char* lastButtonPressPtr )
{
  static unsigned long lastTime = 0;
  unsigned long currentTime = millis();
  bool update = currentTime - lastTime > 1000;

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

      if( *lastButtonPressPtr != 0 ) 
      {

        String buttonPressed = String( *lastButtonPressPtr );

        if( buttonPressed == "B" ) config::setDifficulty( config::difficulty::EASY );
        else if( buttonPressed == "Y" ) config::setDifficulty( config::difficulty::MEDIUM );
        else if( buttonPressed == "A" ) config::setDifficulty( config::difficulty::HARD );

        game::_hasDifficultyBeenSet = true;

        *lastButtonPressPtr = 0;
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

        if( snake::hasWon() ) 
        {
          sequence::gamewonSequence();
          
          softwareReset();
        }
        if( snake::hasLost() )
        {
          sequence::gameoverSequence();
          softwareReset();
        }
        else leds::display( snake::board );
      }
    if( *lastButtonPressPtr != 0 ) 
    {
      snake::enqueueDirection( String( *lastButtonPressPtr ) );
      *lastButtonPressPtr = 0;
    }
  }
}