#include "dcpu_manager.h"
#include "display.h"


int to_ncurses_color(int c)
{
  switch(c)
    {
    case 1: return 4;
    case 3: return 6;
    case 4: return 1;
    case 6: return 3;
    default: return c;
    }
}


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
      nodelay(manager->dcpu_screens[i].wscreen, true);
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

  pairIndex = to_ncurses_color(*(cpu->ram + SCREEN_BORDER_ADDR) & 7);
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
	      pairIndex = (c->text_color << 3) | c->background_color;
	      init_pair(pairIndex, to_ncurses_color(c->text_color), to_ncurses_color(c->background_color));
	      if (c->character == 0)
		mvwaddch(wscreen, y+2, x+2, ' ');
	      else if (c->blink)
		mvwaddch(wscreen, y+2, x+2, c->character | A_BLINK);
	      else
		mvwaddch(wscreen, y+2, x+2, c->character | COLOR_PAIR(pairIndex));
	      //	      wrefresh(wscreen);
	      //return;
	    }
	}
    }
  wrefresh(wscreen);
}

void ncurses_getchar(dcpu16 *cpu, WINDOW *wscreen)
{
  static int pp = 0;

  int c = wgetch(wscreen);
  if (c == ERR)
    return;

  if (cpu->ram[KEYBOARD_ADDR + pp] != 0)
    return;

  cpu->ram[KEYBOARD_ADDR + pp] = (char)c;
  pp = ((pp + 1) & 0xF);
}

void ncurses_refresh(dcpu_manager *manager)
{
  while (true)
    {
      ncurses_getchar(&(manager->dcpus[0]), manager->dcpu_screens[0].wscreen);
      
      for (int i = 0; i < manager->nb_dcpu; ++i)
	{
	  ncurses_screen(&(manager->dcpus[i]), manager->dcpu_screens[i].wscreen);
	  ncurses_registers(&(manager->dcpus[i]), manager->dcpu_screens[i].wregisters);
	}
    }
}
