#include "snake.h"


char snake::board[ leds::SIZE ];


void InitBoard()
{
	for( unsigned short x = 0; x < leds::WIDTH; x++ )
	{
		for( unsigned short y = 0; y < leds::HEIGHT; y++ )
		{
			 snake::board[ y * leds::HEIGHT + x ] = ' ';
		}
	}
}