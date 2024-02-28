#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

#define LED_PIN     13  // Define the pin connected to the NeoPixels
#define NUM_LEDS    100  // Number of LEDs you are controlling

namespace leds
{
  const uint8_t WIDTH = 6;
  const uint8_t HEIGHT = 14;

  const uint8_t SIZE = WIDTH * HEIGHT;

  extern Adafruit_NeoPixel _leds;

  void init();
  void display( char* board );
}

#endif