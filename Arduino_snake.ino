#include <avr/wdt.h>
#include "leds.h"
#include "colors.h"
#include "snake.h"
#include "digits.h"
#include "sequences.h"

volatile char lastButtonPress = 0;
uint64_t previousMillis = 0; 
static const char allowedChars[] = { 'U','D','L','R','Y','A','B','X' };

void setup() 
{
  randomSeed( analogRead( 0 ) );
  Serial.begin( 115200 );

  config::setDifficulty( config::difficulty::EASY );

  leds::init();
  snake::initBoard();
  snake::initSnake();
  snake::initFood();

  flags::canProcessInput = false; 

}


void loop() 
{
  if( !sequence::isStartupSequenceDone ) sequence::startupSequence();

  if( flags::canProcessInput )
  {
    uint64_t currentMillis = millis();
    bool updateGameState = currentMillis - previousMillis >= config::getGameConfig().UPDATE_DELAY;

    if( updateGameState ) 
    {
      previousMillis = currentMillis;
      
      snake::move();

      if( snake::hasWon() ) 
      {
        sequence::gamewonSequence();
        
        softwareReset();
      }
      if( snake::hasLost() )
      {
        sequence::gameoverSequence();
        softwareReset();
      }
      else leds::display( snake::board );
    }

    if( lastButtonPress != 0 ) 
    {
      snake::enqueueDirection( String( lastButtonPress ) );
      lastButtonPress = 0;
    }
  }
}


void serialEvent() 
{
  if( Serial.available() > 0 ) 
  {
    char inChar = (char)Serial.read();

    // Filter out non-directional characters
    for( uint8_t i = 0; i < sizeof( allowedChars ) / sizeof( allowedChars[ 0 ] ); i++ ) 
    {
      if( inChar == allowedChars[ i ] && flags::canProcessInput )  { lastButtonPress = inChar; break;  }
    }
  }
}

void softwareReset() 
{
  wdt_enable( WDTO_15MS );
  while( true ) {} 
}