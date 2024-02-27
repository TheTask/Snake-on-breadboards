#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"


namespace config 
{
    const uint8_t  INIT_SNAKE_LENGTH = 3;
    const uint8_t  BOARD_BRIGHTNESS = 10;
    const uint32_t BORDER_COLOR = colors::LIGHT_RED;
    const uint32_t FOOD_COLOR = colors::WHITE;

    enum difficulty
    {
      EASY,
      MEDIUM,
      HARD
    }

    inline _difficulty = difficulty::EASY;

    struct gameConfig 
    {
      const uint32_t SNAKE_COLOR;
      const float    SPEED;

      gameConfig( uint32_t snakeColor,float speed )
          : 
          SNAKE_COLOR( snakeColor ),
          SPEED( speed )
          {}
    };

    inline gameConfig getGameConfig() 
    {
        switch( _difficulty ) 
        {
            case EASY:
                return gameConfig( colors::GREEN,1.0 ); 
            case MEDIUM:
                return gameConfig( colors::BLUE,2.0 ); 
            case HARD:
                return gameConfig( colors::RED,3.0 ); 
        }
    }
}

#endif 