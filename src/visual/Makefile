INCFLAGS = -I vecmath/include
INCFLAGS += -I/usr/local/include

CC = g++
CFLAGS = -g -Wall -ansi -arch x86_64
SRCS = $(wildcard *.cpp)
SRCS += $(wildcard vecmath/src/*.cpp)
OBJS = $(SRCS:.cpp=.o)
PROG = a4

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LINKFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

clean:
	rm -f *.bak vecmath/src/*.o *.o core.* $(PROG) 
