#include "leds.h"
#include "snake_io.h"
#include "colors.h"
#include "snake.h"

String inputString = "";    // A string to hold incoming data
bool stringComplete = true;  // Whether the string is complete

volatile char lastChar = 0;
unsigned long previousMillis = 0; // Stores the last time the game state was updated
const long interval = 200;

void setup() 
{
  randomSeed( analogRead( 0 ) );
  Serial.begin( 115200 );
  inputString.reserve( 200 );  // Reserve 200 bytes for the inputString

  config::setDifficulty( config::difficulty::EASY );

  leds::init();

  snake::initBoard();
  snake::initSnake();
  snake::initFood();
}

void loop() 
{
  if( snake::hasEatenFood() ) 
  {
    FoodSegment segment = FoodSegment( snake::food_row,snake::food_col );
    snake::snake_vec.push_back( segment );
    snake::initFood();
  }

  unsigned long currentMillis = millis();

  if( currentMillis - previousMillis >= interval ) 
  {
    previousMillis = currentMillis;

    leds::display( snake::board);
    snake::move( snake::lastDir);

    if( snake::hasWon() ) {}
    if( snake::hasLost() ) {}
  }

  if( lastChar != 0 ) 
  {
    String direction = String( lastChar );
    snake::direction newDir = snake::str2dir(direction);
    snake::lastDir = newDir;
    
    lastChar = 0; 
  }
}

void serialEvent() {
  const char allowedChars[] = { 'U','D','L','R','Y','A','B','X' };

  if( Serial.available() > 0 ) 
  {
    char inChar = (char)Serial.read();

    // Filter out non-directional characters
    for( int i = 0; i < sizeof( allowedChars ) / sizeof( allowedChars[ 0 ] ); i++ ) 
    {
      if( inChar == allowedChars[ i ] )  { lastChar = inChar; break;  }
    }
  }
}