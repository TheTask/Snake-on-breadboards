#include "sequences.h"

void sequence::startupSequence() 
{
  uint64_t currentMillis = millis();
  bool update = currentMillis - sequence::_previousMillis >= sequence::_oneSecondDelay;

  switch( sequence::_currentState ) 
  {
    case sequence::startupState::INIT:
      leds::clear();
      sequence::_previousMillis = currentMillis;
      sequence::_currentState = sequence::startupState::SHOW_DIGIT_3;
      break;

    case sequence::startupState::SHOW_DIGIT_3:
      if( update ) 
      {
        leds::displayDigit( digits::digit_3,config::getGameConfig().SNAKE_BODY_COLOR );
        sequence::_currentState = sequence::startupState::SHOW_DIGIT_2;
        sequence::_previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_2:
      if( update ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_2,config::getGameConfig().SNAKE_BODY_COLOR );
        sequence::_currentState = sequence::startupState::SHOW_DIGIT_1;
        sequence::_previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_1:
      if( update ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_1,config::getGameConfig().SNAKE_BODY_COLOR );
        sequence::_currentState = sequence::startupState::DONE;
        sequence::_previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::DONE:
      if( update ) 
      {
        leds::clear();
        flags::canProcessInput = true; 
        sequence::isStartupSequenceDone = true;
      }
      break;
  }
}


void sequence::gameoverSequence()
{
  delay( sequence::_halfSecondDelay );

  leds::drawSpiral( sequence::_fiveMsDelay,sequence::_spiralColor );
  
  delay( sequence::_twoSecondDelay );
}


void sequence::gamewonSequence()
{
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 6,6,2,colors::CYAN );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 5,5,4,colors::YELLOW );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 4,4,6,colors::BLUE );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 3,3,8,colors::RED );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 2,2,10,colors::WHITE );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 1,1,12,colors::MAGENTA );
  delay( sequence::_halfSecondDelay );

  leds::drawSquare( 0,0,14,colors::GREEN );

  delay( sequence::_fiveteenSecondDelay );
}