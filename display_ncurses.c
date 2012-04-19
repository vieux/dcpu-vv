#include "display_ncurses.h"
#define TWEAKCOLOR(c) ( ( ((c) & 1) ^ ((c) & 4) ? ((c)+3)%6 : (c))  )

static WINDOW *wscreen;
static WINDOW *wtitle;
static WINDOW *wregisters;


void init_ncurses()
{
  atexit( (void *)endwin );
  initscr(); 
  cbreak();
  curs_set(0);
  noecho();
  start_color();
  clear();

  wtitle = newwin(3, NBCOLS + 24 + 4, 0, 0);
  wscreen = newwin(NBROWS+4, NBCOLS +4, 3, 0);
  wregisters = newwin(NBROWS+4, 24, 3, NBCOLS+4);

  box(wscreen, 0, 0); 
  box(wtitle, 0, 0); 
  box(wregisters, 0, 0); 

  mvwprintw(wtitle, 1, 24, "[dcpu-vv]");
  wrefresh(wtitle);

  mvwprintw(wregisters, 3, 2, "Key   Value  [Value]");
  wrefresh(wregisters);
}


void registers_ncurses(dcpu16 *cpu)
{
  mvwprintw(wregisters, 1, 2, "Cycle:%14ld", cpu->cycle);
  for (int i = 0; i < 8; ++i)
    mvwprintw(wregisters, 4 + i, 2, "%c:   0x%.4x [0x%.4x]", registers[i], cpu->r[i], cpu->ram[cpu->r[i]]);
  mvwprintw(wregisters, 12, 2, "PC:  0x%.4x [0x%.4x]", cpu->pc, cpu->ram[cpu->pc]);
  mvwprintw(wregisters, 13, 2, "SP:  0x%.4x [0x%.4x]", cpu->sp, cpu->ram[cpu->sp]);
  mvwprintw(wregisters, 14, 2, "O:   0x%.4x [0x%.4x]", cpu->o, cpu->ram[cpu->o]);

  wrefresh(wregisters);
}

void refresh_ncurses(dcpu16 *cpu)
{
  display_character *c;
  short pairIndex;

  pairIndex = TWEAKCOLOR(*(cpu->ram + VIDEO_ADDR + 0x280) & 7);
  init_pair(pairIndex, 0, pairIndex);
  chtype border = ' ' | COLOR_PAIR(pairIndex);

  for (int y = -1; y < NBROWS +1 ; ++y)
    {
      for (int x = -1 ; x < NBCOLS +1 ; ++x)
	{
	  if (x == -1 || y == -1 || x == NBCOLS || y == NBROWS)
	      mvwaddch(wscreen, y+2, x+2, border);
	  else
	    {
	      c = (display_character*) cpu->ram + VIDEO_ADDR + x + y*0x20;
	      pairIndex = TWEAKCOLOR(c->text_color & 0x7)+ TWEAKCOLOR(c->background_color & 0x7);
	      init_pair(pairIndex, TWEAKCOLOR(c->text_color & 0x7), TWEAKCOLOR(c->background_color & 0x7));
	      if (c->character == 0)
		mvwaddch(wscreen, y+2, x+2, ' ');
	      else if (c->blink)
		mvwaddch(wscreen, y+2, x+2, c->character | A_BLINK);
	      else
		mvwaddch(wscreen, y+2, x+2, c->character | COLOR_PAIR(pairIndex));
	    }
	}
    }

  wrefresh(wscreen);
  registers_ncurses(cpu);
}
