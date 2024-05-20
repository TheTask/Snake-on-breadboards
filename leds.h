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

  void sevenSegmentDisplayWrite( uint8_t input );

  void displayBoard( const uint8_t* board,uint8_t snakeHeadLinearIndex );
  void displayDigit( const char* digit,uint32_t color );
  void displayPixel( uint8_t pixelIndex,uint32_t color );
  void displayColor( uint32_t color );
  void displayConfigScene();

  void drawSquare( uint8_t topLeftCornerRow,uint8_t topLeftCornerCol,uint8_t sideLength,uint32_t color );
  void _drawHorizontalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color );
  void _drawVerticalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color );
  
  void drawSpiral( int16_t delayMs,uint32_t color );
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color );
}

#endif