#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
#include <Vector.h>

const int VECTOR_MAX_ELEMENTS = 200;
extern int storage_array[];


namespace snake
{
  enum direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };

  extern Vector< Segment > snake_vec;
  extern uint8_t board[];

  extern uint8_t food_row;
  extern uint8_t food_col;

  void initBoard();
  void initSnake();
  void initFood();
  void move( snake::direction lastDir );

  boolean hasEatenFood();
  void deleteEndOfSnake();

  bool hasWon();
  bool hasLost();
}


#endif