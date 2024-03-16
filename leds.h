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

  void init();
  void clear();

  void display( const uint8_t* board );
  void displayDigit( const char* digit,uint32_t color );
  void displayPixel( uint8_t pixelIndex,uint32_t color );
  void displayColor( uint32_t color );
  void displayConfigScene();
}

#endif