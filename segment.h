#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>

class Segment
{
  protected:
    uint8_t _row;
    uint8_t _col;

  protected:
    Segment(){}
	  Segment( uint8_t row,uint8_t col ) 
      : 
      _row( row ), 
      _col( col ) 
      {}

  public:
    bool operator==( const Segment& other ) const 
    {
        return _row == other._row && _col == other._col;
    }
};


class SnakeSegment : public Segment 
{
  public:
    SnakeSegment() : Segment() {}
    SnakeSegment( uint8_t row,uint8_t col ) : Segment( row,col ) {}

    inline void incRow(){ this->_row++; }
    inline void incCol(){ this->_col++; }
    inline void decRow(){ this->_row--; }
    inline void decCol(){ this->_col--; }

    inline uint8_t getRow() const { return this->_row; }
    inline uint8_t getCol() const { return this->_col; }
};


class FoodSegment : public Segment
{
  public:
    FoodSegment() : Segment() {}
    FoodSegment( uint8_t row,uint8_t col ) : Segment( row,col ) {}
};


#endif