#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>

class Segment
{
  private:
    uint8_t row;
    uint8_t col;

  public:
    Segment(){}
	  Segment( uint8_t row,uint8_t col ) : row(row), col(col) {}

    inline uint8_t getRow() const { return this->row; }
    inline uint8_t getCol() const { return this->col; }

    inline void incRow(){ ++row; }
    inline void incCol(){ ++col; }
    inline void decRow(){ --row; }
    inline void decCol(){ --col; }

    bool operator==( const Segment& other ) const 
    {
        return row == other.row && col == other.col;
    }
};

class SnakeSegment : public Segment 
{
  public: using Segment::Segment; 
};

class FoodSegment : public Segment
{
  public: using Segment::Segment; 
};

#endif