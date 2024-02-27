#ifndef SNAKE_SEGMENT_H
#define SNAKE_SEGMENT_H

#include <stdint.h>

class SnakeSegment
{
  private:
    uint8_t x;
    uint8_t y;

  public:
	  SnakeSegment( uint8_t x,uint8_t y ) : x(x), y(y) {}

    bool operator==( const SnakeSegment& other ) const 
    {
        return x == other.x && y == other.y;
    }
};

#endif