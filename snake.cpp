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
		snake::snakeVec.push_back( segment );
		snake::board[ ( leds::HEIGHT / 2 * leds::WIDTH ) + i + 1 ] = 'O';
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

  leds::displayBoard( snake::board,snake::linearSnakeHeadIndex );
}


void snake::move() 
{

  if( !snake::_directionQueue.isEmpty() ) 
  {
    int8_t nextDirInt;
    snake::_directionQueue.pop( &nextDirInt );
    snake::lastDir = static_cast< snake::direction >( nextDirInt );
  }

  SnakeSegment head = snake::snakeVec.back();

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
  snake::linearSnakeHeadIndex = head.getRow() * leds::WIDTH + head.getCol();
  snake::snakeVec.push_back( head );
  
  if( !snake::hasWon() )
  {
    if( head == snake::_food ) snake::initFood();
    else snake::deleteEndOfSnake();
  }

  snake::board[ snake::linearSnakeHeadIndex ] = 'O';
}


void snake::enqueueDirection( String direction ) 
{
  int8_t dir = -1;
  snake::direction lastTmpDir;

  if( !snake::_directionQueue.isEmpty() ) 
  {
    int8_t lastQueueEntry;
    snake::_directionQueue.peekPrevious( &lastQueueEntry );
    lastTmpDir = static_cast< snake::direction >( lastQueueEntry );
  } 
  else lastTmpDir = snake::lastDir;

       if( ( direction == "U" || direction == "Y" ) && !( lastTmpDir == snake::direction::DOWN || lastTmpDir == snake::direction::UP ) ) dir = static_cast< int8_t >( snake::direction::UP );
  else if( ( direction == "D" || direction == "A" ) && !( lastTmpDir == snake::direction::UP || lastTmpDir == snake::direction::DOWN ) ) dir = static_cast< int8_t >( snake::direction::DOWN );
  else if( ( direction == "R" || direction == "B" ) && !( lastTmpDir == snake::direction::LEFT || lastTmpDir == snake::direction::RIGHT ) ) dir = static_cast< int8_t >( snake::direction::RIGHT );
  else if( ( direction == "L" || direction == "X" ) && !( lastTmpDir == snake::direction::RIGHT || lastTmpDir == snake::direction::LEFT ) ) dir = static_cast< int8_t >( snake::direction::LEFT );

  if( dir >= 0 && dir <= 3 ) snake::_directionQueue.push( &dir ); 
} 


void snake::deleteEndOfSnake()
{
  SnakeSegment tail = snake::snakeVec[ 0 ];

  snake::board[ tail.getRow() * leds::WIDTH + tail.getCol() ] = ' ';	
	snake::snakeVec.remove( 0 ); 
}


bool snake::hasWon()
{
  return snake::snakeVec.size() == leds::SIZE - 2 * ( leds::WIDTH - 1 ) - 2 * ( leds::HEIGHT - 1 );
}
 

bool snake::hasLost()
{ 
  SnakeSegment head = snake::snakeVec.back();

  if( head.getRow() == leds::HEIGHT - 1 || head.getCol() == leds::WIDTH - 1 ||  head.getRow() == 0 || head.getCol() == 0 ) return true;

  for( uint8_t i = 0; i < snake::snakeVec.size() - 1; i++ )
	{
		if( head == snake::snakeVec[ i ] ) return true;
	}
  return false; 
}
