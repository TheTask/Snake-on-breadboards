#ifndef SEQUENCES_H
#define SEQUENCES_H
 
#include "config.h"
#include "leds.h"
#include "digits.h"

namespace sequence
{
  inline bool isStartupSequenceDone = false;
  void startupSequence();
  void gameoverSequence();

  inline const uint8_t _delay_ms = 15;
  void _movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelDown(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelLeft(  uint8_t numPixels,uint8_t* currentPixelIndex );
  void _movePixelUp(    uint8_t numPixels,uint8_t* currentPixelIndex );
}

#endif