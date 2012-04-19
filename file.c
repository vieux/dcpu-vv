#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dcpu16.h"

bool loadBinaryFile(dcpu16 *cpu, FILE *fp)
{
  fread(cpu->ram, 1, 0x10000, fp);
  fclose(fp);
  return true;
}

bool loadHexFile(dcpu16 *cpu, FILE *fp)
{
  u16 i = 0;
  char buf[5];

  while (!feof(fp) && fgets(buf, 5, fp) > 0)
    {
      if (!isalnum(buf[0]))continue;
      cpu->ram[i++] = strtoul(buf, 0, 16); 
    }
  fclose(fp);
  return true;
}


bool loadFile(dcpu16 *cpu)
{
  FILE *fp;

  char buf[10];
  int mode = 0;

  fp = fopen(cpu->program_name, "r");
  if (fp == NULL) 
    return false;

  size_t read = fread(buf, 1, 9, fp);
  buf[read] = 0;
 
  for (int i = 0; i < read; ++i)
    (buf[i] >= '0' && buf[i] <= '9') ? mode++  : mode--;

  rewind(fp);

  if (mode > 0)
    return loadHexFile(cpu, fp);
  return loadBinaryFile(cpu, fp);
}
