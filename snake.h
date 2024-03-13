#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
#include "flags.h"
#include <Vector.h>
#include <cppQueue.h>

namespace snake
{
  enum direction
  {
    UP,
    DOWN,
    LEFT,
    RIGHT
  }
  inline lastDir = snake::direction::UP;
  inline cppQueue	_directionQueue( sizeof( snake::direction ),5,FIFO );	

  inline Segment _storage[ leds::SIZE ];
  inline Vector< Segment > snake_vec( _storage );
  inline uint8_t board[ leds::SIZE ];

  inline FoodSegment food;

  void enqueueDirection( String direction );
  
  void initBoard();
  void initSnake();
  void initFood();
  void move();
  
  void deleteEndOfSnake();

  bool hasWon();
  bool hasLost();
}


#endif