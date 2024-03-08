#ifndef SEQUENCES_H
#define SEQUENCES_H
 
#include "config.h"
#include "leds.h"
#include "digits.h"
#include "flags.h"
#include "snake.h"

namespace sequence
{
  inline volatile bool isStartupSequenceDone = false;
  void startupSequence();

  enum startupState {
        INIT,
        SHOW_DIGIT_3,
        SHOW_DIGIT_2,
        SHOW_DIGIT_1,
        DONE
    };

  inline startupState currentState = INIT;
  inline unsigned long previousMillis = 0; // Stores the last time the sequence updated
  inline const long interval = 1000; // Interval at which to step through the sequence (1 second)


  void gameoverSequence();

  inline const uint8_t _delay_ms = 15;
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex );
}

#endif