#include "dcpu_manager.h"

void usage(char **av) 
{
  printf("%s: <--noscreen> [file.hex|file.bin]\n", av[0]);
}


int main(int ac, char **av)
{
  dcpu_manager manager;

  manager.nb_dcpu = NB_DCPU;
  manager.dcpus = calloc(NB_DCPU, sizeof(dcpu16));
  manager.dcpu_screens = calloc(NB_DCPU, sizeof(dcpu_screen));
  manager.dcpu_threads = calloc(NB_DCPU, sizeof(pthread_t));
  
  manager.dcpus[0].program_name = strdup("./test.bin");
  manager.dcpus[1].program_name = strdup("./test.bin");
  manager.dcpus[2].program_name = strdup("./test.bin");


  ncurses_init(&manager);

  for (int i = 0; i < manager.nb_dcpu; ++i)
    {
      //printf("Creating dcpu16 #%d ==> %s\n", i,  manager.dcpus[i].program_name);
      pthread_create(&(manager.dcpu_threads[i]), NULL, dcpu_start, &(manager.dcpus[i]));
    }		     
  
  ncurses_refresh(&manager);
  while(true);
  return 0;
}
