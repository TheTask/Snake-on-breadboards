#ifndef SNAKE_H
#define SNAKE_H

#include "segment.h"
#include "leds.h"
#include <Vector.h>
#include <cppQueue.h>

#define VECTOR_MAX_ELEMENTS 200


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
  inline cppQueue	directionQueue( sizeof( snake::direction ),5,FIFO );	

  inline Segment _storage[ VECTOR_MAX_ELEMENTS ];
  inline Vector< Segment > snake_vec( _storage );
  inline uint8_t board[ leds::SIZE ];

  inline uint8_t food_row;
  inline uint8_t food_col;

  void enqueueDirection( String direction );
  
  void initBoard();
  void initSnake();
  void initFood();
  void move();

  boolean hasEatenFood();
  
  void deleteEndOfSnake();

  bool hasWon();
  bool hasLost();
}


#endif