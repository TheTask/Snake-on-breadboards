#include "leds.h"

void leds::init()
{
    _leds.begin(); 
    _leds.setBrightness( config::BOARD_BRIGHTNESS );
    leds::clear();
}

void leds::display( const uint8_t* board )
{
  for( uint8_t i = 0; i < leds::SIZE; i++ )
  {
         if( board[ i ] == '/' ) _leds.setPixelColor( i,config::getGameConfig().BORDER_COLOR );
    else if( board[ i ] == 'O' ) _leds.setPixelColor( i,config::getGameConfig().SNAKE_COLOR );
    else if( board[ i ] == 'X' ) _leds.setPixelColor( i,config::FOOD_COLOR );
    else if( board[ i ] == ' ' ) _leds.setPixelColor( i,colors::OFF );
  }

  _leds.show();
}


void leds::clear()
{
  for( uint8_t i = 0; i < leds::SIZE; i++ ) _leds.setPixelColor( i,colors::OFF );

  _leds.show();
}


void leds::displayDigit( const char* digit,uint32_t color )
{
  for( uint8_t row = 0; row < leds::HEIGHT; row++ )
  {
    uint8_t col_index = 0;

    for( col_index; col_index < 4; col_index++ )
       _leds.setPixelColor( row * leds::WIDTH + col_index,colors::OFF );

    for( uint8_t col = 0; col < 6; col++,col_index++ )
    {
       if( digit[ row * 6 + col ] ) _leds.setPixelColor( row * leds::WIDTH + col_index,color );
    }

    for( col_index; col_index < 14; col_index++ )
       _leds.setPixelColor( row * leds::WIDTH + col_index,colors::OFF );
  }

  _leds.show();
}

void leds::displayPixel( uint8_t pixelIndex,uint32_t color )
{
  _leds.setPixelColor( pixelIndex,color );
  _leds.show();
}

void leds::displayColor( uint32_t color )
{
  for( uint8_t i = 0; i < leds::SIZE; i++ ) _leds.setPixelColor( i,color );

  _leds.show();
}


void leds::displayConfigScene()
{
  for( uint8_t i = 0; i < leds::SIZE; i++ )
  {
    if( i % leds::WIDTH >= 0  && i % leds::WIDTH < 4 )  _leds.setPixelColor( i,colors::GREEN );
    if( i % leds::WIDTH >= 5  && i % leds::WIDTH < 9 )  _leds.setPixelColor( i,colors::BLUE );
    if( i % leds::WIDTH >= 10 && i % leds::WIDTH < 14 ) _leds.setPixelColor( i,colors::RED );
  }

  _leds.show();
}

void leds::_drawHorizontalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color )
{
  for( uint8_t i = 0; i < length; i++ )  _leds.setPixelColor( row * leds::WIDTH + col + i,color );
}


void leds::_drawVerticalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color )
{
  for( uint8_t i = 0; i < length; i++ )  _leds.setPixelColor( row * leds::WIDTH + col + ( i * leds::WIDTH ),color );
}


void leds::drawSquare( uint8_t topLeftCornerRow,uint8_t topLeftCornerCol,uint8_t sideLength,uint32_t color )
{
  leds::_drawHorizontalLine( topLeftCornerRow,topLeftCornerCol,sideLength,color );
  leds::_drawHorizontalLine( topLeftCornerRow + sideLength - 1,topLeftCornerCol,sideLength,color );
  leds::_drawVerticalLine( topLeftCornerRow,topLeftCornerCol,sideLength,color );
  leds::_drawVerticalLine( topLeftCornerRow,topLeftCornerCol + sideLength - 1,sideLength,color );

  _leds.show();
}
