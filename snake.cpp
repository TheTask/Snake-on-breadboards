#include "snake.h"


uint8_t snake::board[ leds::SIZE ];

SnakeSegment storage[ VECTOR_MAX_ELEMENTS ];
Vector<SnakeSegment> snake::snake_vec( storage );


void snake::initBoard()
{
	for( uint8_t row = 0; row < leds::HEIGHT; row++ )
	{
		for( uint8_t col = 0; col < leds::WIDTH; col++ )
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

void snake::initSnake()
{
	for( uint8_t i = 0; i < config::INIT_SNAKE_LENGTH; i++ )
	{
		SnakeSegment segment = SnakeSegment( i + leds::HEIGHT / 2 ,leds::WIDTH / 2 );
		snake::snake_vec.push_back( segment );
		snake::board[ i + ( leds::HEIGHT / 2 * leds::WIDTH + leds::WIDTH / 2 ) ] = 'O';
	}
}
