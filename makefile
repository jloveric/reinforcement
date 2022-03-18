# In absence of working cmake for c++20 modules using plain old make
CC := g++
#CFLAGS := -Wall -g -std=c++20 -fmodules-ts -lstdc++
CFLAGS := -Wall -g -std=c++20 -lstdc++
TARGET := grid_world

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $@ $^
%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o
	
.PHONY: all clean