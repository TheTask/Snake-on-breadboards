#include "leds.h"

void leds::init()
{
  leds::_leds.begin(); 
  leds::_leds.setBrightness( config::BOARD_BRIGHTNESS );
  leds::clear();
}


void leds::sevenSegmentDisplayWrite( uint8_t input ) 
{
  for( uint8_t i = 0; i < 8; i++ ) 
  {
    if( input & ( 1 << i ) ) digitalWrite( leds::dataPins[ i ],HIGH ); 
    else digitalWrite( leds::dataPins[ i ],LOW ); 
  }
}


void leds::displayBoard( const uint8_t* board,uint8_t snakeHeadLinearIndex )
{
  for( uint8_t i = 0; i < leds::SIZE; i++ )
  {
         if( board[ i ] == '/' ) leds::_leds.setPixelColor( i,config::getGameConfig().BORDER_COLOR );
    else if( board[ i ] == 'O' ) leds::_leds.setPixelColor( i,config::getGameConfig().SNAKE_BODY_COLOR );
    else if( board[ i ] == 'X' ) leds::_leds.setPixelColor( i,config::FOOD_COLOR );
    else if( board[ i ] == ' ' ) leds::_leds.setPixelColor( i,colors::OFF );
  }
  leds::_leds.setPixelColor( snakeHeadLinearIndex,config::getGameConfig().SNAKE_HEAD_COLOR );

  leds::_leds.show();
}


void leds::clear()
{
  for( uint8_t i = 0; i < leds::SIZE; i++ ) leds::_leds.setPixelColor( i,colors::OFF );

  leds::_leds.show();
}


void leds::displayDigit( const char* digit,uint32_t color )
{
  for( uint8_t row = 0; row < leds::HEIGHT; row++ )
  {
    uint8_t col_index = 0;

    for( col_index; col_index < 4; col_index++ )
       leds::_leds.setPixelColor( row * leds::WIDTH + col_index,colors::OFF );

    for( uint8_t col = 0; col < 6; col++,col_index++ )
    {
       if( digit[ row * 6 + col ] ) leds::_leds.setPixelColor( row * leds::WIDTH + col_index,color );
    }

    for( col_index; col_index < 14; col_index++ )
       leds::_leds.setPixelColor( row * leds::WIDTH + col_index,colors::OFF );
  }

  leds::_leds.show();
}


void leds::displayPixel( uint8_t pixelIndex,uint32_t color )
{
  leds::_leds.setPixelColor( pixelIndex,color );
  leds::_leds.show();
}


void leds::displayColor( uint32_t color )
{
  for( uint8_t i = 0; i < leds::SIZE; i++ ) leds::_leds.setPixelColor( i,color );

  leds::_leds.show();
}


void leds::displayConfigScene()
{
  for( uint8_t i = 0; i < leds::SIZE; i++ )
  {
    if( i % leds::WIDTH >= 0  && i % leds::WIDTH < 4 )  leds::_leds.setPixelColor( i,colors::GREEN );
    if( i % leds::WIDTH >= 5  && i % leds::WIDTH < 9 )  leds::_leds.setPixelColor( i,colors::BLUE );
    if( i % leds::WIDTH >= 10 && i % leds::WIDTH < 14 ) leds::_leds.setPixelColor( i,colors::RED );
  }

  leds::_leds.show();
}


void leds::drawSquare( uint8_t topLeftCornerRow,uint8_t topLeftCornerCol,uint8_t sideLength,uint32_t color )
{
  leds::_drawHorizontalLine( topLeftCornerRow,topLeftCornerCol,sideLength,color );
  leds::_drawHorizontalLine( topLeftCornerRow + sideLength - 1,topLeftCornerCol,sideLength,color );
  leds::_drawVerticalLine( topLeftCornerRow,topLeftCornerCol,sideLength,color );
  leds::_drawVerticalLine( topLeftCornerRow,topLeftCornerCol + sideLength - 1,sideLength,color );

  leds::_leds.show();
}


void leds::_drawHorizontalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color )
{
  for( uint8_t i = 0; i < length; i++ )  leds::_leds.setPixelColor( row * leds::WIDTH + col + i,color );
}


void leds::_drawVerticalLine( uint8_t row,uint8_t col,uint8_t length,uint32_t color )
{
  for( uint8_t i = 0; i < length; i++ )  leds::_leds.setPixelColor( row * leds::WIDTH + col + ( i * leds::WIDTH ),color );
}


void leds::drawSpiral( int16_t delayMs,uint32_t color )
{
  uint8_t pixelIndex = 0;
  uint8_t* currentPixelIndex = &pixelIndex;

  uint8_t initHeight = leds::HEIGHT;
  uint8_t initWidth = leds::WIDTH;

  //draws a basic spiral on top of existing image
  _movePixelRight( leds::WIDTH,currentPixelIndex,delayMs,color  );

  for( uint8_t i = 0; i < leds::WIDTH / 2; i++ )
  {
    leds::_movePixelDown( initHeight--,currentPixelIndex,delayMs,color );
    leds::_movePixelLeft( initWidth--,currentPixelIndex,delayMs,color );
    leds::_movePixelUp( initHeight--,currentPixelIndex,delayMs,color );
    leds::_movePixelRight( initWidth--,currentPixelIndex,delayMs,color );
  }
}


void leds::_movePixelRight( uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( (*currentPixelIndex)++,color );
    delay( delayMs );
  }
  (*currentPixelIndex)--;
}


void leds::_movePixelDown( uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color  )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( (*currentPixelIndex)+= leds::WIDTH,color );
    delay( delayMs );
  }
  (*currentPixelIndex)-= leds::WIDTH;
}


void leds::_movePixelLeft( uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color  )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( (*currentPixelIndex)--,color );
    delay( delayMs );
  }
  (*currentPixelIndex)++;
}


void leds::_movePixelUp( uint8_t numPixels,uint8_t* currentPixelIndex,int16_t delayMs,uint32_t color  )
{
  for( uint8_t i = 0; i < numPixels; i++ )
  {
    leds::displayPixel( (*currentPixelIndex)-= leds::WIDTH,color);
    delay( delayMs );
  }
  (*currentPixelIndex)+= leds::WIDTH;
}
