#include "snake.h"

void snake::initBoard()
{
	for( uint8_t row = 0; row < leds::HEIGHT; row++ )
	{
		for( uint8_t col = 0; col < leds::WIDTH; col++ )
		{
      if( row == 0 || row == leds::HEIGHT - 1 || col == 0 || col == leds::WIDTH - 1 )
        snake::board[ row * leds::WIDTH + col ] = '/';
      else
        snake::board[ row * leds::WIDTH + col ] = ' ';
		}
	}
}


void snake::initSnake()
{
	for( uint8_t i = 0; i < config::INIT_SNAKE_LENGTH; i++ )
	{
		SnakeSegment segment = SnakeSegment( leds::HEIGHT / 2,i + 1 ); 
		snake::snake_vec.push_back( segment );
		snake::board[ i + ( leds::HEIGHT / 2 * leds::WIDTH ) + 1 ] = 'O';
	}
}


void snake::initFood()
{
  do 
  {
    uint8_t foodRow = random( 1,leds::HEIGHT - 1 );
    uint8_t foodCol = random( 1,leds::WIDTH - 1 );

    if( snake::board[ foodRow * leds::WIDTH + foodCol ] == ' ' ) 
    {
      snake::_food = FoodSegment( foodRow,foodCol );
      snake::board[ foodRow * leds::WIDTH + foodCol ] = 'X';
      break;
    }
  } 
  while( true );

  leds::display( snake::board );
}


void snake::move() 
{
  if( !snake::_directionQueue.isEmpty() ) 
  {
    int8_t nextDirInt;
    snake::_directionQueue.pop( &nextDirInt );

    snake::direction nextDir = static_cast< snake::direction >( nextDirInt );
    snake::lastDir = nextDir;
  }

  Segment head = snake::snake_vec.back();

  switch( snake::lastDir ) 
  {
    case snake::direction::UP:
      head.decRow();
      break;
    case snake::direction::DOWN:
      head.incRow();
      break;
    case snake::direction::LEFT:
      head.decCol();
      break;
    case snake::direction::RIGHT:
      head.incCol();
      break;
  }

  if( head == snake::_food ) initFood();
  else deleteEndOfSnake();

  snake::snake_vec.push_back( head );
  snake::board[ head.getRow() * leds::WIDTH + head.getCol() ] = 'O';
}


void snake::enqueueDirection( String direction ) 
{
  int8_t dir = -1;
  snake::direction lastDir;

  if( !snake::_directionQueue.isEmpty() ) 
  {
    int8_t peekDirInt;
    snake::_directionQueue.peek( &peekDirInt );
    lastDir = static_cast< snake::direction >( peekDirInt );
  } 
  else lastDir = snake::lastDir;

       if( ( direction == "U" || direction == "Y" ) && ( lastDir != snake::direction::DOWN ) )  dir = static_cast< int8_t >( snake::direction::UP );
  else if( ( direction == "D" || direction == "A" ) && ( lastDir != snake::direction::UP ) )    dir = static_cast< int8_t >( snake::direction::DOWN );
  else if( ( direction == "R" || direction == "B" ) && ( lastDir != snake::direction::LEFT ) )  dir = static_cast< int8_t >( snake::direction::RIGHT );
  else if( ( direction == "L" || direction == "X" ) && ( lastDir != snake::direction::RIGHT ) ) dir = static_cast< int8_t >( snake::direction::LEFT );

  if( dir != -1 ) snake::_directionQueue.push( &dir );
}


void snake::deleteEndOfSnake()
{
  Segment tail = snake::snake_vec[ 0 ];

  snake::board[ tail.getRow() * leds::WIDTH + tail.getCol() ] = ' ';	
	snake::snake_vec.remove( 0 ); 
}


bool snake::hasWon()
{
  return snake::snake_vec.size() == leds::SIZE - ( 2 * leds::WIDTH + 2 * ( leds::HEIGHT - 2 ) );
}
 

bool snake::hasLost()
{ 
  Segment head = snake::snake_vec.back();

  if( head.getRow() == leds::HEIGHT - 1 || head.getCol() == leds::WIDTH - 1 ||  head.getRow() == 0 || head.getCol() == 0 ) return true;

  for( uint8_t i = 0; i < snake::snake_vec.size() - 1; i++ )
	{
		if( head == snake::snake_vec[ i ] ) return true;
	}
  return false; 
}
