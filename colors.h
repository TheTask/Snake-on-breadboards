#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

namespace colors 
{
    // 0xWWGGRRBB
    static const uint32_t GREEN = 0x00FF0000; 
    static const uint32_t RED = 0x0000FF00;
    static const uint32_t BLUE = 0x000000FF;

    static const uint32_t MAGENTA = RED | BLUE;
    static const uint32_t YELLOW = GREEN | RED;
    static const uint32_t CYAN = GREEN | BLUE;

    static const uint32_t WHITE = 0xFFFFFFFF;
    static const uint32_t OFF = 0x00000000; 

    
}


#endif 