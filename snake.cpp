#include "snake.h"


uint8_t snake::board[ leds::SIZE ];

Segment storage[ VECTOR_MAX_ELEMENTS ];
Vector<Segment> snake::snake_vec( storage );
uint8_t snake::food_row;
uint8_t snake::food_col;


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
		SnakeSegment segment = SnakeSegment( i + leds::HEIGHT / 2 ,0 ); //roughly middle screen
		snake::snake_vec.push_back( segment );
		snake::board[ i + ( leds::HEIGHT / 2 * leds::WIDTH ) ] = 'O';
	}
}

void snake::initFood()
{
  snake::food_row = random( leds::HEIGHT );
  snake::food_col = random( leds::WIDTH );

  while( snake::board[ snake::food_row * leds::WIDTH + snake::food_col ] != ' ' )
  {
    snake::food_row = random( leds::HEIGHT );
    snake::food_col = random( leds::WIDTH );
  }

	snake::board[ snake::food_row * leds::WIDTH + snake::food_col  ] = 'X';
}

void snake::move( snake::direction lastDir )
{ 
  Segment segment = snake::snake_vec.at( snake::snake_vec.size() - 1 );

  switch( lastDir )
  {
    case snake::direction::DOWN:
      segment.incCol();
      break;
    case snake::direction::LEFT:
      segment.incRow();
      break;
    case snake::direction::UP:
      segment.decCol();
      break;
    case snake::direction::RIGHT:
      segment.decCol();
      break;
  }

  snake::snake_vec.push_back( segment );
  snake::board[ segment.getRow() * leds::WIDTH + segment.getCol() ];
  snake::deleteEndOfSnake();
} 


boolean snake::hasEatenFood()
{
  Segment snake = snake::snake_vec.at( snake::snake_vec.size() - 1 );
	FoodSegment food = FoodSegment( snake::food_row,snake::food_col );

	return snake == food;
}

void snake::deleteEndOfSnake()
{
  uint8_t row = snake::snake_vec[ 0 ].getRow();
  uint8_t col = snake::snake_vec[ 0 ].getCol();

  if( row == 0 || row == leds::HEIGHT - 1 || col == 0 || col == leds::WIDTH - 1 )
  {
    snake::board[ row * leds::WIDTH + col ] = '/'; //update back to border if it was a border
  }
  else
  {
    snake::board[ row * leds::WIDTH + col ] = ' ';
  }
	
	snake::snake_vec.remove( 0 ); 
}

bool snake::hasWon(){ return false; }
bool snake::hasLost(){ return false; }
