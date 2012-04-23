#include "dcpu_manager.h"
#include "display.h"

#define TWEAKCOLOR(c) ( ( ((c) & 1) ^ ((c) & 4) ? ((c)+3)%6 : (c))  )

void ncurses_init(dcpu_manager *manager)
{
  initscr(); 
  cbreak();
  curs_set(0);
  noecho();
  start_color();
  clear();

  atexit((void *)endwin);

  for (int i = 0; i < manager->nb_dcpu; ++i)  
    {
      manager->dcpu_screens[i].wtitle = newwin(TITLE_ROWS, TITLE_COLS, 0, i*TITLE_COLS);
      manager->dcpu_screens[i].wscreen = newwin(SCREEN_ROWS, SCREEN_COLS, TITLE_ROWS, i*TITLE_COLS);
      manager->dcpu_screens[i].wregisters = newwin(REGISTERS_ROWS, REGISTERS_COLS, TITLE_ROWS, i*TITLE_COLS + SCREEN_COLS);
      
      box(manager->dcpu_screens[i].wscreen, 0, 0); 
      box(manager->dcpu_screens[i].wtitle, 0, 0); 
      box(manager->dcpu_screens[i].wregisters, 0, 0); 

      mvwprintw(manager->dcpu_screens[i].wtitle, 1, 24, "[dcpu-vv]");
      wrefresh(manager->dcpu_screens[i].wtitle);
      
      mvwprintw(manager->dcpu_screens[i].wregisters, 3, 2, "Key   Value  [Value]");
      wrefresh(manager->dcpu_screens[i].wregisters);
    }
}


void ncurses_registers(dcpu16 *cpu, WINDOW *wregisters)
{
  mvwprintw(wregisters, 1, 2, "Cycle:%14ld", cpu->cycle);
  for (int i = 0; i < 8; ++i)
    mvwprintw(wregisters, 4 + i, 2, "%c:   0x%.4x [0x%.4x]", registers[i], cpu->r[i], cpu->ram[cpu->r[i]]);
  mvwprintw(wregisters, 12, 2, "PC:  0x%.4x [0x%.4x]", cpu->pc, cpu->ram[cpu->pc]);
  mvwprintw(wregisters, 13, 2, "SP:  0x%.4x [0x%.4x]", cpu->sp, cpu->ram[cpu->sp]);
  mvwprintw(wregisters, 14, 2, "O:   0x%.4x [0x%.4x]", cpu->o, cpu->ram[cpu->o]);

  wrefresh(wregisters);
}

void ncurses_screen(dcpu16 *cpu, WINDOW *wscreen)
{
  dcpu_character *c;
  short pairIndex;

  pairIndex = TWEAKCOLOR(*(cpu->ram + SCREEN_BORDER_ADDR) & 7);
  init_pair(pairIndex, 0, pairIndex);
  chtype border = ' ' | COLOR_PAIR(pairIndex);

  for (int y = -1; y < DCPU_ROWS +1 ; ++y)
    {
      for (int x = -1 ; x < DCPU_COLS +1 ; ++x)
	{
	  if (x == -1 || y == -1 || x == DCPU_COLS || y == DCPU_ROWS)
	      mvwaddch(wscreen, y+2, x+2, border);
	  else
	    {
	      c = (dcpu_character*) cpu->ram + VIDEO_ADDR + x + y*0x20;
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
}

void ncurses_refresh(dcpu_manager *manager)
{
  while (true)
    {
      for (int i = 0; i < manager->nb_dcpu; ++i)
	{
	  ncurses_screen(&(manager->dcpus[i]), manager->dcpu_screens[i].wscreen);
	  ncurses_registers(&(manager->dcpus[i]), manager->dcpu_screens[i].wregisters);
	}
    }
}
