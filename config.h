#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"

namespace config 
{
  static const uint8_t  INIT_SNAKE_LENGTH = 3;
  static const uint8_t  BOARD_BRIGHTNESS = 10;
  static const uint32_t FOOD_COLOR = colors::WHITE;

  enum difficulty
  {
    EASY,
    MEDIUM,
    HARD
  }

  inline _difficulty = difficulty::EASY;
  inline void setDifficulty( config::difficulty difficulty ){ _difficulty = difficulty; }
  
  struct gameConfig 
  {
    const uint32_t SNAKE_COLOR;
    const uint32_t BORDER_COLOR;
    const uint64_t UPDATE_DELAY;

    gameConfig( uint32_t snakeColor,uint32_t borderColor,uint64_t updateDelay )
      : 
      SNAKE_COLOR( snakeColor ),
      BORDER_COLOR( borderColor ),
      UPDATE_DELAY( updateDelay )
      {}
  };

  inline gameConfig getGameConfig() 
  {
    switch( _difficulty ) 
    {
      case EASY:
          return gameConfig( colors::GREEN,colors::MAGENTA,300 ); 
      case MEDIUM:
          return gameConfig( colors::BLUE,colors::YELLOW,200 ); 
      case HARD:
          return gameConfig( colors::RED,colors::CYAN,100 ); 
    }
  }
}


#endif 