#ifndef SEQUENCES_H
#define SEQUENCES_H
 
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

  static const uint8_t  _fiveMsDelay     = 5;
  static const uint16_t _halfSecondDelay = 500; 
  static const uint16_t _oneSecondDelay  = 1000; 
  static const uint16_t _twoSecondDelay  = 2000; 
  static const uint16_t _fiveteenSecondDelay = 15000; 
  

  inline startupState _currentState = startupState::INIT;
  inline volatile bool isStartupSequenceDone = false;
  static const uint32_t _spiralColor = colors::RED;
  
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex );

  void startupSequence();
  void gameoverSequence();
  void gamewonSequence();
}

#endif