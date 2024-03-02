#include "sequences.h"


void sequence::startupSequence()
{
  leds::clear();

  leds::displayDigit( digits::digit_3,colors::RED );
  delay( 1000 );
  leds::clear();

  leds::displayDigit( digits::digit_2,colors::RED );
  delay( 1000 );
  leds::clear();

  leds::displayDigit( digits::digit_1,colors::RED );
  delay( 1000 );
  leds::clear();
  
  sequence::isStartupSequenceDone = true;
}

void sequence::gameoverSequence()
{
  uint8_t pixelIndex = 0;
  uint8_t* currentPixelIndex = &pixelIndex;

  uint8_t initHeight = 14;
  uint8_t initWidth = 6;

  _movePixelRight( 6,currentPixelIndex );

  
  for( int i = 0; i < leds::WIDTH / 2; i++ )
  {
    _movePixelDown( initHeight--,currentPixelIndex );
    _movePixelLeft( initWidth--,currentPixelIndex );
    _movePixelUp( initHeight--,currentPixelIndex );
    _movePixelRight( initWidth--,currentPixelIndex );
  }
  
  delay( 3000 );
}


void sequence::_movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    (*currentPixelIndex)++;
    delay( delay_ms );
  }
  (*currentPixelIndex)--;
}

void sequence::_movePixelDown( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    *currentPixelIndex += leds::WIDTH;
    delay( delay_ms );
  }
  (*currentPixelIndex)-= leds::WIDTH;
}

void sequence::_movePixelLeft( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    (*currentPixelIndex)--;
    delay( delay_ms );
  }
  (*currentPixelIndex)++;
}
void sequence::_movePixelUp( uint8_t numPixels,uint8_t* currentPixelIndex )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( *currentPixelIndex,colors::RED );
    *currentPixelIndex -= leds::WIDTH;
    delay( delay_ms );
  }
  (*currentPixelIndex)+= leds::WIDTH;
}