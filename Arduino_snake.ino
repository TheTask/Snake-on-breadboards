#include <avr/wdt.h>
#include "game.h"

volatile char lastButtonPress = 0;
char* lastButtonPressPtr = &lastButtonPress;

static const char allowedChars[] = { 'U','D','L','R','Y','A','B','X','T','F' };

void setup() 
{
  for ( uint8_t i = 0; i < 8; i++ ) pinMode( leds::dataPins[ i ],OUTPUT );
    
  Serial.begin( 115200 );
  while( !Serial ); 

  randomSeed( randomSeed() );
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

    if( !flags::canProcessInput ) return;

    for( uint8_t i = 0; i < sizeof( allowedChars ) / sizeof( allowedChars[ 0 ] ); i++ ) 
    {
      if( inChar == allowedChars[ i ] )
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


uint16_t randomSeed()
{
  uint16_t sum = 0;

  for( uint8_t i = 0; i < 8; i++ ) sum += analogRead( i );

  return sum;
}