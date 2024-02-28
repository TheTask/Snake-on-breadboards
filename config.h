#ifndef CONFIG_H
#define CONFIG_H

#include "colors.h"


namespace config 
{
    const uint8_t  INIT_SNAKE_LENGTH = 3;
    const uint8_t  BOARD_BRIGHTNESS = 10;
    const uint32_t FOOD_COLOR = colors::WHITE;

    enum difficulty
    {
      EASY,
      MEDIUM,
      HARD
    }

    inline _difficulty = difficulty::EASY;

    inline setDifficulty( config::difficulty difficulty )
    {
      _difficulty = difficulty;
    }

    struct gameConfig 
    {
      const uint32_t SNAKE_COLOR;
      const uint32_t BORDER_COLOR;
      const float    SPEED;

      gameConfig( uint32_t snakeColor,uint32_t borderColor,float speed )
          : 
          SNAKE_COLOR( snakeColor ),
          BORDER_COLOR( borderColor ),
          SPEED( speed )
          {}
    };

    inline gameConfig getGameConfig() 
    {
        switch( _difficulty ) 
        {
            case EASY:
                return gameConfig( colors::GREEN,colors::LIGHT_BLUE ^ colors::LIGHT_RED,1.0 ); 
            case MEDIUM:
                return gameConfig( colors::BLUE,colors::LIGHT_GREEN ^ colors::LIGHT_RED,2.0 ); 
            case HARD:
                return gameConfig( colors::RED,colors::LIGHT_BLUE ^ colors::LIGHT_GREEN,3.0 ); 
        }
    }
}

#endif 