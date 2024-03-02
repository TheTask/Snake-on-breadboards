#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdint.h>

class Segment
{
  private:
    uint8_t _row;
    uint8_t _col;

  public:
    Segment(){}
	  Segment( uint8_t row,uint8_t col ) 
      : 
      _row( row ), 
      _col( col ) 
      {}

    inline uint8_t getRow() const { return this->_row; }
    inline uint8_t getCol() const { return this->_col; }

    inline void incRow(){ this->_row++; }
    inline void incCol(){ this->_col++; }
    inline void decRow(){ this->_row--; }
    inline void decCol(){ this->_col--; }

    bool operator==( const Segment& other ) const 
    {
        return _row == other._row && _col == other._col;
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