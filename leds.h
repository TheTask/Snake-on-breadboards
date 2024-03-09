#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

#define LED_PIN     13 
#define NUM_LEDS    196  

namespace leds
{
  const uint8_t WIDTH = 14;
  const uint8_t HEIGHT = 14;

  const uint8_t SIZE = WIDTH * HEIGHT;

  extern Adafruit_NeoPixel _leds;

  void init();
  void display( uint8_t* board );
  void clear();

  void displayDigit( bool* digit,uint32_t color );
  void displayPixel( uint8_t pixelIndex,uint32_t color );
}

#endif