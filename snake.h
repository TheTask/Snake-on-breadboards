#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
#include <Vector.h>

const int VECTOR_MAX_ELEMENTS = 200;
extern int storage_array[];


namespace snake
{
  extern Vector<SnakeSegment> snake_vec;
  extern uint8_t board[];

  void initBoard();
  void initSnake();
}



#endif