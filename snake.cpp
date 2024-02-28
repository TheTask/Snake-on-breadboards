#include "snake.h"


char snake::board[ leds::SIZE ];


void snake::initBoard()
{
	for( unsigned short row = 0; row < leds::HEIGHT; row++ )
	{
		for( unsigned short col = 0; col < leds::WIDTH; col++ )
		{
      if( row == 0 || row == leds::HEIGHT - 1 || col == 0 || col == leds::WIDTH - 1 )
      {
        snake::board[ row * leds::WIDTH + col ] = '/'; //border
      }
      else
      {
        snake::board[ row * leds::WIDTH + col ] = ' ';
      }
		}
	}
}