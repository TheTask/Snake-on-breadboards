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

  inline uint64_t _previousMillis = 0; 
  static const uint64_t _oneSecondDelay = 1000; 
  static const uint8_t _fiveMsDelay = 5;

  inline startupState _currentState = startupState::INIT;
  inline volatile bool isStartupSequenceDone = false;
  static uint32_t _spiralColor;
  
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex );

  void _drawSpiral();


  void startupSequence();
  void gameoverSequence();
  void gamewonSequence();
}

#endif