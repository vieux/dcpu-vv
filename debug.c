#include "debug.h"



void dumpRegisters(FILE *fp, dcpu16 *cpu)
{
  for (int i = 0; i < 8; ++i)
    fprintf(fp, "%c:\t0x%x\t[0x%x]\n", registers[i], cpu->r[i], cpu->ram[cpu->r[i]]);
}

void dumpFlags(FILE *fp, dcpu16 *cpu)
{
  fprintf(fp, "PC:\t0x%x\t[0x%x]\n", cpu->pc, cpu->ram[cpu->pc]);
  fprintf(fp, "SP:\t0x%x\t[0x%x]\n", cpu->sp, cpu->ram[cpu->sp]);
  fprintf(fp, "O:\t0x%x\t[0x%x]\n", cpu->o, cpu->ram[cpu->o]);
}

void fullDump(FILE *fp, dcpu16 *cpu, u16 size)
{
  for (u16 i = 0 ; i < size; i += 8)
    {
      fprintf(fp, "%04x: %04x %04x %04x %04x %04x %04x %04x %04x\n", i, cpu->ram[i], cpu->ram[i+1], cpu->ram[i+2],cpu->ram[i+3],cpu->ram[i+4],cpu->ram[i+5],cpu->ram[i+6],cpu->ram[i+7]);
    }
}
