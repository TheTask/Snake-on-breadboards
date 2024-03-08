#include "sequences.h"

void sequence::startupSequence() 
{
  uint64_t currentMillis = millis();

  switch( sequence::currentState ) 
  {
    case sequence::startupState::INIT:
      leds::clear();
      sequence::previousMillis = currentMillis;
      sequence::currentState = sequence::startupState::SHOW_DIGIT_3;
      break;

    case sequence::startupState::SHOW_DIGIT_3:
      if( currentMillis - sequence::previousMillis >= sequence::delayBetweenDigets ) 
      {
        leds::displayDigit( digits::digit_3, colors::RED );
        sequence::currentState = sequence::startupState::SHOW_DIGIT_2;
        sequence::previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_2:
      if( currentMillis - sequence::previousMillis >= sequence::delayBetweenDigets ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_2,colors::RED );
        sequence::currentState = sequence::startupState::SHOW_DIGIT_1;
        sequence::previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::SHOW_DIGIT_1:
      if( currentMillis - sequence::previousMillis >= sequence::delayBetweenDigets ) 
      {
        leds::clear();
        leds::displayDigit( digits::digit_1,colors::RED );
        sequence::currentState = sequence::startupState::DONE;
        sequence::previousMillis = currentMillis;
      }
      break;

    case sequence::startupState::DONE:
      if( currentMillis - sequence::previousMillis >= sequence::delayBetweenDigets ) 
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
  
  delay( 3000 );
  leds::clear();
}


void sequence::_movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    (*currentPixelIndex)++;
    delay( _delay_ms );
  }
  (*currentPixelIndex)--;
}

void sequence::_movePixelDown( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    (*currentPixelIndex)+= leds::WIDTH;
    delay( _delay_ms );
  }
  (*currentPixelIndex)-= leds::WIDTH;
}

void sequence::_movePixelLeft( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    (*currentPixelIndex)--;
    delay( _delay_ms );
  }
  (*currentPixelIndex)++;
}
void sequence::_movePixelUp( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    *currentPixelIndex -= leds::WIDTH;
    delay( _delay_ms );
  }
  (*currentPixelIndex)+= leds::WIDTH;
}