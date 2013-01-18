#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "dcpu16.h"
#include "debug.h"

#define CORE_RAM_SIZE 0x9020

static void core(char *str, dcpu16 *cpu)
{
  FILE *fp;
  char *core_filename;

  asprintf(&core_filename, "%s.core", cpu->program_name);
  fp = fopen(core_filename, "w+");
  free(core_filename);
  if (fp == NULL)
    return;
  fprintf(fp, "[ERROR] %s at ox%x\n\n", str, cpu->pc);
  dumpRegisters(fp, cpu);
  dumpFlags(fp, cpu);
  fullDump(fp, cpu, CORE_RAM_SIZE);

  fclose(fp);
}

void error(char *str, dcpu16 *cpu)
{
  
  if (cpu != NULL)
    {
      fprintf(stderr, "[ERROR] %s as 0x%x, generating core file...\n", str, cpu->pc);
      core(str, cpu);
    }
  else
    fprintf(stderr, "[ERROR] %s, generating core file...\n", str);
  exit(EXIT_FAILURE);
}


