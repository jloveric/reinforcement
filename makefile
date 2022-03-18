# In absence of working cmake for c++20 modules using plain old make
CC := g++
CFLAGS := -Wall -g -std=c++20 -fmodules-ts -lstdc++
TARGET := grid_world

SRCS := $(wildcard *.cxx)
OBJS := $(patsubst %.cxx,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cxx
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean