#include "stdlib.h"
#include "debug.h"

void init_console()
{

}

void refresh_console(dcpu16 *cpu)
{
  system("clear");
  dumpRegisters(stdout, cpu);
  dumpFlags(stdout, cpu);
  fullDump(stdout, cpu, 0x20);
}
