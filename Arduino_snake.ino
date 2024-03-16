#include <avr/wdt.h>
#include "game.h"

volatile char lastButtonPress = 0;
char* lastButtonPressPtr = &lastButtonPress;

static const char allowedChars[] = { 'U','D','L','R','Y','A','B','X','T','F' };

void setup() 
{
  Serial.begin( 115200 );
  while( !Serial ); 

  flags::canProcessInput = true; 
  randomSeed( analogRead( 0 ) );
}


void loop() 
{
  game::game( lastButtonPressPtr );
}


void serialEvent() 
{
  if( Serial.available() > 0 ) 
  {
    char inChar = (char)Serial.read();

    for( uint8_t i = 0; i < sizeof( allowedChars ) / sizeof( allowedChars[ 0 ] ); i++ ) 
    {
      if( inChar == allowedChars[ i ] && flags::canProcessInput )
      { 
        *lastButtonPressPtr = inChar; 
        break;  
      }
    }
  }
}


void softwareReset() 
{
  wdt_enable( WDTO_15MS );
  while( true ) {} 
}