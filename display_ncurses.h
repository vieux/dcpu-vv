#ifndef _NCURSES_
# define _NCURSES_

#include <ncurses.h>
#include <stdlib.h>

#include "dcpu16.h"
#include "debug.h"

#define NBROWS 12
#define NBCOLS 32

typedef union	display_character
{
  u16		value;
  struct
  {
    u16		character : 7;
    u16		blink : 1;
    u16		background_color : 4;
    u16		text_color : 4;
  };
}		display_character;

#endif
