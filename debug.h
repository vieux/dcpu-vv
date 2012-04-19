#ifndef _DEBUG_
# define _DEBUG_

#include <stdio.h>

#include "dcpu16.h"

void dumpRegisters(FILE *fp, dcpu16 *cpu);
void dumpFlags(FILE *fp, dcpu16 *cpu);
void fullDump(FILE *fp, dcpu16 *cpu, u16 size);

#endif
