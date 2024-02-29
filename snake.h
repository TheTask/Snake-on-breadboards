#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
#include <Vector.h>

const int VECTOR_MAX_ELEMENTS = 200;
extern int storage_array[];


namespace snake
{
  extern Vector< Segment > snake_vec;
  extern uint8_t board[];

  extern uint8_t food_row;
  extern uint8_t food_col;

  enum direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  }

  inline lastDir = snake::direction::UP;
  

  void initBoard();
  void initSnake();
  void initFood();
  void move( snake::direction lastDir );
  snake::direction str2dir( String direction );

  boolean hasEatenFood();
  void deleteEndOfSnake();

  bool hasWon();
  bool hasLost();
}


#endif