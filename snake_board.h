#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

#define LED_PIN     13  // Define the pin connected to the NeoPixels
#define NUM_LEDS    100  // Number of LEDs you are controlling


namespace board
{
  extern Adafruit_NeoPixel _leds;

  void init(config::difficulty difficulty);
  void display();
  Adafruit_NeoPixel& getHandle();
}

#endif