#ifndef _NCURSES_
# define _NCURSES_

#include <ncurses.h>
#include <stdlib.h>

#include "dcpu16.h"

#define VIDEO_ADDR 0x8000
#define SCREEN_BORDER_ADDR  0x8280
#define KEYBOARD_ADDR 0x9000

#define DCPU_ROWS 12
#define DCPU_COLS 32

#define SCREEN_ROWS (DCPU_ROWS + 4)
#define SCREEN_COLS (DCPU_COLS + 4)

#define REGISTERS_ROWS SCREEN_ROWS
#define REGISTERS_COLS 24

#define TITLE_ROWS 3
#define TITLE_COLS (SCREEN_COLS + REGISTERS_COLS)

typedef struct	dcpu_screen
{
  WINDOW	*wtitle;
  WINDOW	*wscreen;
  WINDOW	*wregisters;
}		dcpu_screen;

typedef union	dcpu_character
{
  u16		value;
  struct
  {
    u16		character : 7;
    u16		blink : 1;
    u16		background_color : 4;
    u16		text_color : 4;
  };
}		dcpu_character;

#endif
