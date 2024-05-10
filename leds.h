#ifndef LEDS_H
#define LEDS_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

#define LED_PIN     13 

namespace leds
{
  const uint8_t WIDTH = 14;
  const uint8_t HEIGHT = 14;

  const uint8_t SIZE = WIDTH * HEIGHT;

  inline Adafruit_NeoPixel _leds( leds::SIZE,LED_PIN,NEO_GRB + NEO_KHZ800 );

  const uint8_t dataPins[ 8 ] = { 5,6,7,8,9,10,11,12 };

  void init();
  void clear();

  void seventSegmentDisplayWrite( uint8_t input );

  void displayBoard( const uint8_t* board );
  void displayDigit( const char* digit,uint32_t color );
  void displayPixel( uint8_t pixelIndex,uint32_t color );
  void displayColor( uint32_t color );
  void displayConfigScene();

  void _drawHorizontalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color );
  void _drawVerticalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color );
  void drawSquare( uint8_t topLeftCornerRow,uint8_t topLeftCornerCol,uint8_t sideLength,uint32_t color );
}

#endif