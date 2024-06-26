#ifndef COLORS_H
#define COLORS_H

#include <stdint.h>

namespace colors 
{
  // 0xWWGGRRBB
  static const uint32_t BRIGHT_GREEN   = 0x00FF0000; 
  static const uint32_t BRIGHT_RED     = 0x0000FF00;
  static const uint32_t BRIGHT_BLUE    = 0x000000FF;

  static const uint32_t GREEN          = 0x00440000; 
  static const uint32_t RED            = 0x00004400;
  static const uint32_t BLUE           = 0x00000044;

  static const uint32_t BRIGHT_MAGENTA = BRIGHT_RED | BRIGHT_BLUE;
  static const uint32_t MAGENTA        = BLUE  | RED;
  static const uint32_t YELLOW         = GREEN | RED;
  static const uint32_t CYAN           = GREEN | BLUE;

  static const uint32_t BRIGHT_WHITE   = 0xFFFFFFFF;
  static const uint32_t WHITE          = 0x44444444;
  static const uint32_t OFF            = 0x00000000; 
}


#endif 