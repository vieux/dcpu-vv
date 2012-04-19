#include <stdlib.h>
#include <stdio.h>

#include "dcpu16.h"

static u16 literals[0x20] = {
  0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
  0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
  0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
  0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
};

inline u8 opcode_pc_cost(u16 code)
{
  switch (code)
    {
    case 0x10 ... 0x17:
    case 0x1e:
    case 0x1f:
      return 1;
    default:
      return 0;
    }
}
u16* access_opcode(dcpu16 *cpu, u16 code, char c)
{
  switch (code)
    {
    case 0x00 ... 0x07: return cpu->r + code;
    case 0x08 ... 0x0f: return cpu->ram + cpu->r[code & 7];
    case 0x10 ... 0x17: return cpu->ram + cpu->ram[cpu->pc++] + cpu->r[code & 7];
    case 0x18: return cpu->ram + cpu->sp++;
    case 0x19: return cpu->ram + cpu->sp;
    case 0x1a: return cpu->ram + (--(cpu->sp));
    case 0x1b: return &cpu->sp;
    case 0x1c: return &cpu->pc;
    case 0x1d: return &cpu->o;
    case 0x1e: return cpu->ram + cpu->ram[cpu->pc++];
    case 0x1f: return cpu->ram + cpu->pc++;
    case 0x20 ... 0x3f: return literals + (code & 0x1f);
    default: error("Illegal Opcode", cpu); return NULL;
    }
}

opcode_infos basic_opcodes[0x10] = {
  {"ERR",  0},
  {"SET", 1},
  {"ADD", 2},
  {"SUB", 2},
  {"MUL", 2},
  {"DIV", 3},
  {"MOD", 3},
  {"SHL", 2},
  {"SHR", 2},
  {"AND", 1},
  {"BOR", 1},
  {"XOR", 1},
  {"IFE", 2},
  {"IFN", 2},
  {"IFG", 2},
  {"IFB", 2}
};

opcode_infos non_basic_opcodes[] = {
  {"ERR", 0},
  {"JSR", 2}
};
