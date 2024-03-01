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
		SnakeSegment segment = SnakeSegment( leds::HEIGHT / 2,i + 1 ); //roughly middle screen
		snake::snake_vec.push_back( segment );
		snake::board[ i + ( leds::HEIGHT / 2 * leds::WIDTH ) + 1 ] = 'O';
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
      segment.incRow();
      break;
    case snake::direction::LEFT:
      segment.decCol();
      break;
    case snake::direction::UP:
      segment.decRow();
      break;
    case snake::direction::RIGHT:
      segment.incCol();
      break;
  }

  snake::snake_vec.push_back( segment );
  snake::board[ segment.getRow() * leds::WIDTH + segment.getCol() ] = 'O';
  snake::deleteEndOfSnake();
} 


snake::direction snake::str2dir(String direction)
{
       if( ( direction == "U" || direction == "Y" ) && snake::lastDir != snake::direction::DOWN )  return snake::direction::UP;
  else if( ( direction == "D" || direction == "A" ) && snake::lastDir != snake::direction::UP )    return snake::direction::DOWN;
  else if( ( direction == "R" || direction == "B" ) && snake::lastDir != snake::direction::LEFT )  return snake::direction::RIGHT;
  else if( ( direction == "L" || direction == "X" ) && snake::lastDir != snake::direction::RIGHT ) return snake::direction::LEFT;

  return snake::lastDir;
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


bool snake::hasWon()
{
  bool space = false;

  for( uint8_t i = 0; i < leds::SIZE; i++ )
  {
    	if( snake::board[ i ] == ' ' )
      {
        space = true;
        break;
      }
  }

  return !space;
}
 

bool snake::hasLost()
{ 
  Segment segment = snake::snake_vec.at( snake::snake_vec.size() - 1 );

  if( segment.getRow() < 0 || 
		  segment.getRow() > leds::HEIGHT - 1 || 
		  segment.getCol() < 0 ||
		  segment.getCol() > leds::WIDTH - 1 ) return true;

  for( uint8_t i = 0; i < snake::snake_vec.size() - 1; i++ )
	{
		Segment current = snake::snake_vec[ i ];
		if( current == segment ) return true;
	}
  return false; 
}
