#ifndef _DCPU_MANAGER_
# define _DCPU_MANAGER_

#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#include "display.h"

#define NB_DCPU 3

typedef struct	dcpu_manager
{
  int		nb_dcpu;
  dcpu16	*dcpus;
  dcpu_screen	*dcpu_screens;
  pthread_t	*dcpu_threads;
}		dcpu_manager;

void ncurses_init(dcpu_manager *manager);
void ncurses_refresh(dcpu_manager *manager);

#endif 
