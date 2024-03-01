#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

namespace colors 
{
    // 0xWWGGRRBB
    const uint32_t GREEN = 0x00FF0000; 
    const uint32_t RED = 0x0000FF00;
    const uint32_t BLUE = 0x000000FF;
    const uint32_t LIGHT_GREEN = 0x00330000;
    const uint32_t LIGHT_RED = 0x00003300;
    const uint32_t LIGHT_BLUE = 0x00000033;
    const uint32_t WHITE = 0xFFFFFFFF;

    const uint32_t OFF = 0x00000000; 

    const uint32_t SNAKE = colors::GREEN | colors::RED;
}


#endif 