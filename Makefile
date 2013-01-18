CC := gcc
CFLAGS := -Wall -g -std=c99 -fms-extensions
LDFLAGS := -lcurses
OUT_NAME := dcpu-vv
UNAME := $(shell uname)


ifeq ($(UNAME), Darwin)
	LDFLAGS += -lpthread
else
	LDFLAGS += -pthread	
endif

all: $(OUT_NAME)

DCPU_OBJS := dcpu16.o opcodes.o file.o operations.o error.o display.o debug.o registers.o dcpu_manager.o
$(OUT_NAME): $(DCPU_OBJS)
	$(CC) -o $(OUT_NAME) $(DCPU_OBJS) $(LDFLAGS)

fclean: clean
	rm -f $(OUT_NAME)
clean:
	rm -f *.o
	rm -f *~

re: fclean all
