#include "dcpu_manager.h"

void usage(char **av) 
{
  fprintf(stderr, "%s: [file.hex|file.bin ....]\n", av[0]);
}

bool opts(int ac, char **av, dcpu_manager *manager)
{
  if (ac == 1)
    return false;
  
  manager->nb_dcpu = ac - 1;
  manager->dcpus = calloc(manager->nb_dcpu, sizeof(dcpu16));
  manager->dcpu_screens = calloc(manager->nb_dcpu, sizeof(dcpu_screen));
  manager->dcpu_threads = calloc(manager->nb_dcpu, sizeof(pthread_t));

  for (int i = 1; i < ac; ++i)
    manager->dcpus[i-1].program_name = av[i];    
  return true;
}


int main(int ac, char **av)
{
  dcpu_manager manager;

  if (opts(ac, av, &manager))
    {
      ncurses_init(&manager);
     
      for (int i = 0; i < manager.nb_dcpu; ++i)
	{
	  //printf("Creating dcpu16 #%d ==> %s\n", i,  manager.dcpus[i].program_name);
	  pthread_create(&(manager.dcpu_threads[i]), NULL, dcpu_start, &(manager.dcpus[i]));
	}		     
      
      ncurses_refresh(&manager);
    }
    else
      usage(av);
  return 0;
}
