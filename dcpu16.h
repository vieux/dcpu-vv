#ifndef _DCPU16_
# define _DCPU16_

#include <stdbool.h>
#include <stdio.h>

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

#define VIDEO_ADDR 0x8000
#define KEYBOARD_ADDR 0x9000

extern char registers[8];

typedef struct	dcpu16 
{
  u16 unused;
  u16 ram[0x10000];
  u16 r[8];
  u16 pc;
  u16 sp;
  u16 o;
  long cycle;

  char *program_name;
  struct	display
  {
    void (*init)();
    void (*refresh)(struct dcpu16 *cpu);
  }		display;
}		dcpu16;

typedef union instruction
{
  u16		value;
  struct 
  {
    u16		opcode	: 4;
    u16		value_a	: 6;
    u16		value_b	: 6;
  };
}		instruction;

typedef struct	opcode_infos
{
  char	str[3];
  u8	cycle_cost;
}		opcode_infos;


/* error.c */
void error(char *str, dcpu16 *cpu);

/* opcodes.c */
u16* access_opcode(dcpu16 *cpu, u16 code, char c);
u8 opcode_pc_cost(u16 code);

/* operations.c */
bool basic_operation(dcpu16 *cpu, u16 code, u16 b, u16 *toSet);
bool extended_operation(dcpu16 *cpu, u16 code , u16 a);

/* file.c */
bool loadFile(dcpu16 *cpu);


void init_console();
void refresh_console(dcpu16 *cpu);

void init_ncurses();
void refresh_ncurses(dcpu16 *cpu);

#endif
