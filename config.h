#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"

namespace config 
{
  static const uint8_t  INIT_SNAKE_LENGTH = 3;
  static const uint8_t  BOARD_BRIGHTNESS = 80;
  static const uint32_t FOOD_COLOR = colors::BRIGHT_MAGENTA;

  enum difficulty
  {
    EASY,
    MEDIUM,
    HARD
  }

  inline _difficulty;
  inline void setDifficulty( config::difficulty difficulty ){ _difficulty = difficulty; }
  
  struct gameConfig 
  {
    const uint32_t SNAKE_HEAD_COLOR;
    const uint32_t SNAKE_BODY_COLOR;
    const uint32_t BORDER_COLOR;
    const uint64_t UPDATE_DELAY;

    gameConfig( uint32_t snakeHeadColor,uint32_t snakeBodyColor,uint32_t borderColor,uint64_t updateDelay )
      : 
      SNAKE_HEAD_COLOR( snakeHeadColor ),
      SNAKE_BODY_COLOR( snakeBodyColor ),
      BORDER_COLOR( borderColor ),
      UPDATE_DELAY( updateDelay )
      {}
  };

  inline gameConfig getGameConfig() 
  {
    switch( _difficulty ) 
    {
      case EASY:
          return gameConfig( colors::BRIGHT_GREEN,colors::GREEN,colors::WHITE,300 ); 
      case MEDIUM:
          return gameConfig( colors::BRIGHT_BLUE,colors::BLUE,colors::YELLOW,200 ); 
      case HARD:
          return gameConfig( colors::BRIGHT_RED,colors::RED,colors::CYAN,100 ); 
    }
  }
}


#endif 