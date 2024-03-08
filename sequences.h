#ifndef SEQUENCES_H
#define SEQUENCES_H
 
#include "config.h"
#include "leds.h"
#include "digits.h"
#include "flags.h"
#include "snake.h"

namespace sequence
{
  enum startupState 
  {
    INIT,
    SHOW_DIGIT_3,
    SHOW_DIGIT_2,
    SHOW_DIGIT_1,
    DONE
  };

  inline startupState currentState = INIT;
  inline uint64_t previousMillis = 0; 
  inline const uint32_t delayBetweenDigets = 1000; 
  inline volatile bool isStartupSequenceDone = false;

  void startupSequence();
  void gameoverSequence();

  inline const uint8_t _delay_ms = 15;
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex );
}

#endif