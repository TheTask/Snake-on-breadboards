#include "leds.h"

// Create an instance of the Adafruit_NeoPixel class called 'leds'.
// Parameter 1 = number of pixels in the strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel leds::_leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


void leds::init()
{
    _leds.begin(); 
    _leds.setBrightness(config::BOARD_BRIGHTNESS);
}

void leds::display( char* board )
{
  uint8_t index = 0;

  for( uint8_t row = 0; row < leds::HEIGHT; row++ )
  {
    for( uint8_t col = 0; col < leds::WIDTH; col++ )
    {
      if( board[ index ] == '/' ) _leds.setPixelColor(index, config::getGameConfig().BORDER_COLOR);
      else if( board[ index ] == 'O' ) _leds.setPixelColor(index, config::getGameConfig().SNAKE_COLOR);
      else if( board[ index ] == ' ' ) _leds.setPixelColor(index, colors::OFF);
      index++;
    }
  }

  _leds.show();
}
