#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
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
  inline lastDir = snake::direction::RIGHT;
  inline cppQueue	_directionQueue( sizeof( snake::direction ),5,FIFO );	

  inline SnakeSegment _storage[ leds::SIZE ];
  inline Vector< SnakeSegment > snake_vec( _storage );
  inline uint8_t board[ leds::SIZE ];

  inline FoodSegment _food;


  void initBoard();
  void initSnake();
  void initFood();

  void enqueueDirection( String direction );
  void move();
  void deleteEndOfSnake();

  bool hasWon();
  bool hasLost();
  inline bool hasGameEnded(){ return hasWon() || hasLost(); }
}


#endif