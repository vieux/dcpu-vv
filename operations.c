#include <stdlib.h>
#include <stdio.h>

#include "dcpu16.h"

extern opcode_infos basic_opcodes[0x10];
extern opcode_infos non_basic_opcodes[];

bool basic_operation(dcpu16 *cpu, u16 code , u16 b, u16 *toSet)
{
  u16 a = *toSet;
  u32 result;

  cpu->cycle += basic_opcodes[code].cycle_cost;
  
  switch (code)
    {
    case 0x1: result = b; break;
    case 0x2: result = a+b; cpu->o = (result >> 16 ? 0x0001 : 0); break;
    case 0x3: result = a-b; cpu->o = (result >> 16 ? 0xFFFF : 0); break;
    case 0x4: result = a*b; cpu->o = (result >> 16); break;
    case 0x5: if (b) {result = a/b; cpu->o = (a << 16) / b; } else {result = cpu->o = 0;}  break;
    case 0x6: if (b) {result = a%b;} else {result = 0;} break;
    case 0x7: result = a<<b; cpu->o = result >> 16; break;
    case 0x8: result = a>>b; cpu->o = ((a<<16)>>b); break;
    case 0x9: result = a&b; break;
    case 0xa: result = a|b; break;
    case 0xb: result = a^b; break;
    case 0xc: return (a != b);
    case 0xd: return (a == b);
    case 0xe: return (a <= b);
    case 0xf: return ((a&b) == 0);
    default:
      error("Invalide Opcode", cpu);
    }

  *toSet = result;
  return false;
}

bool extended_operation(dcpu16 *cpu, u16 code , u16 a)
{
  switch (code)
    {
    case 0x1: cpu->ram[--(cpu->sp)] = cpu->pc; cpu->pc = a; break;
    default: error("Invalide Opcode", cpu);
    }

  cpu->cycle += non_basic_opcodes[code].cycle_cost;
  return false;
}
