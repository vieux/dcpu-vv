
CFLAGS := -Wall -g -std=c99 -fms-extensions
LDFLAGS := -lcurses
OUT_NAME := dcpu-vv

all: $(OUT_NAME)

DCPU_OBJS := dcpu16.o opcodes.o file.o operations.o error.o display_console.o display_ncurses.o debug.o registers.o
$(OUT_NAME): $(DCPU_OBJS)
	$(CC) $(LDFLAGS) -o $(OUT_NAME) $(DCPU_OBJS)

fclean: clean
	rm -f $(OUT_NAME)
clean:
	rm -f *.o
	rm -f *~

re: fclean all
