#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "dcpu16.h"

static inline void skipInstruction(dcpu16 *cpu)
{
  instruction i = {.value = cpu->ram[cpu->pc++]};
 
  cpu->pc += opcode_pc_cost(i.value_a);
  cpu->pc += opcode_pc_cost(i.value_b);
  cpu->cycle++;
}

bool handleInstruction(dcpu16 *cpu)
{
  instruction i = {.value = cpu->ram[cpu->pc++]};

  if (i.opcode == 0) { // non-basic opcodes
    extended_operation(cpu, i.value_a, *access_opcode(cpu, i.value_b));
  } else {
    if (basic_operation(cpu, i.opcode, *access_opcode(cpu, i.value_b), access_opcode(cpu, i.value_a)))
      skipInstruction(cpu);
  }

  return true;
}

/*
void opts(dcpu16 *cpu, int ac, char **av)
{
  cpu->display.init = init_ncurses;
  //  cpu->display.refresh = refresh_ncurses;
  
  for (int i = 1; i < ac; ++i)
    {
      if (strcmp(av[i], "--noscreen") == 0)
	{
	  cpu->display.init = init_console;
	  //  cpu->display.refresh = refresh_console;
	}
      else
	cpu->program_name = av[i];
    }
    }
*/

void* dcpu_start(void *arg)
{
  dcpu16 *cpu = arg;

  //printf("dcpu16 staring... ==> %s\n", cpu->program_name);
  
  if (!loadFile(cpu))
    error("Can't open file", NULL);
 
  while (handleInstruction(cpu))
    {
      usleep(100);
    }
  return NULL;
}
