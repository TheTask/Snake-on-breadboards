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
        leds::displayDigit( digits::digit_3,config::getGameConfig().SNAKE_COLOR );
        sequence::_currentState = sequence::startupState::SHOW_DIGIT_2;
        sequence::_previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_2:
      if( update ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_2,config::getGameConfig().SNAKE_COLOR  );
        sequence::_currentState = sequence::startupState::SHOW_DIGIT_1;
        sequence::_previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_1:
      if( update ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_1,config::getGameConfig().SNAKE_COLOR  );
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
  sequence::_spiralColor = colors::RED;
  sequence::_drawSpiral();
  delay( 2000 );
  leds::clear();
}

void sequence::gamewonSequence()
{
  sequence::_spiralColor = colors::GREEN;
  sequence::_drawSpiral();
  delay( 2000 );
  leds::clear();
}


void sequence::_drawSpiral()
{
  uint8_t pixelIndex = 0;
  uint8_t* currentPixelIndex = &pixelIndex;

  uint8_t initHeight = leds::HEIGHT;
  uint8_t initWidth = leds::WIDTH;

  //draws a basic spiral on top of existing image
  _movePixelRight( leds::WIDTH,currentPixelIndex );

  for( uint8_t i = 0; i < leds::WIDTH / 2; i++ )
  {
    _movePixelDown( initHeight--,currentPixelIndex );
    _movePixelLeft( initWidth--,currentPixelIndex );
    _movePixelUp( initHeight--,currentPixelIndex );
    _movePixelRight( initWidth--,currentPixelIndex );
  }
}


void sequence::_movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,sequence::_spiralColor );
    (*currentPixelIndex)++;
    delay( _fiveMsDelay );
  }
  (*currentPixelIndex)--;
}

void sequence::_movePixelDown( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,sequence::_spiralColor );
    (*currentPixelIndex)+= leds::WIDTH;
    delay( _fiveMsDelay );
  }
  (*currentPixelIndex)-= leds::WIDTH;
}

void sequence::_movePixelLeft( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,sequence::_spiralColor );
    (*currentPixelIndex)--;
    delay( _fiveMsDelay );
  }
  (*currentPixelIndex)++;
}
void sequence::_movePixelUp( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,sequence::_spiralColor );
    (*currentPixelIndex)-= leds::WIDTH;
    delay( _fiveMsDelay );
  }
  (*currentPixelIndex)+= leds::WIDTH;
}