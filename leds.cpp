#include "leds.h"

// Create an instance of the Adafruit_NeoPixel class called 'leds'.
// Parameter 1 = number of pixels in the strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel leds::_leds(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);


void leds::init(config::difficulty difficulty)
{
    _leds.begin(); 
    _leds.setBrightness(config::BOARD_BRIGHTNESS);
}

void leds::display( char* board )
{
      for(int i = 0; i < leds::SIZE; i++)
  {
        _leds.setPixelColor(board[i], colors::RED); // Set the first pixel to red
  }
    _leds.show();
}


Adafruit_NeoPixel& leds::getHandle()
{
    return _leds;
}
