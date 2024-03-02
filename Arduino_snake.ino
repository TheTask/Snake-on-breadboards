#include <avr/wdt.h>
#include "leds.h"
#include "colors.h"
#include "snake.h"
#include "digits.h"
#include "sequences.h"

volatile char lastButtonPress = 0;

uint64_t previousMillis = 0; 

void setup() 
{
  randomSeed( analogRead( 0 ) );
  Serial.begin( 115200 );

  config::setDifficulty( config::difficulty::MEDIUM );

  leds::init();

  snake::initBoard();
  snake::initSnake();
  snake::initFood();
}


void loop() 
{
  if( !sequence::isStartupSequenceDone ) sequence::startupSequence();

  uint64_t currentMillis = millis();

  if( currentMillis - previousMillis >= config::getGameConfig().UPDATE_DELAY ) 
  {
    previousMillis = currentMillis;

    if( snake::hasEatenFood() ) 
    {
      FoodSegment segment = FoodSegment( snake::food_row,snake::food_col );
      snake::snake_vec.push_back( segment );
      snake::initFood();
    }
    snake::move();

    if( snake::hasWon() ) {}
    if( snake::hasLost() )
    {
      sequence::gameoverSequence();
      softwareReset();
    }

    leds::display( snake::board );
  }

  if( lastButtonPress != 0 ) 
  {
    snake::enqueueDirection( String( lastButtonPress ) );
    lastButtonPress = 0;
  }
}


void serialEvent() 
{
  const char allowedChars[] = { 'U','D','L','R','Y','A','B','X' };

  if( Serial.available() > 0 ) 
  {
    char inChar = (char)Serial.read();

    // Filter out non-directional characters
    for( uint8_t i = 0; i < 8; i++ ) 
    {
      if( inChar == allowedChars[ i ] )  { lastButtonPress = inChar; break;  }
    }
  }
}

void softwareReset() 
{
  wdt_enable( WDTO_15MS );
  while( true ) {} 
}