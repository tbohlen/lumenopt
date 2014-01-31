# for shared types file
INCFLAGS = -I ../../include
INCFLAGS += -I .
# for boost
INCFLAGS += -I /usr/local/include

LINKFLAGS = -L.

PROG = model
MAIN_SRC = main.cpp
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)

CC = g++
CFLAGS = -g -Wall -ansi -arch x86_64
ALL_MAIN_SRCS = $(wildcard *.cpp)
ALL_MAIN_SRCS += $(wildcard ../vecmath/*.cpp)
MAIN_SRCS = $(filter-out $(MAIN_SRC), $(ALL_MAIN_SRCS))
TEST_SRCS = $(wildcard test/*.cpp)

# find all object files
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.cpp=.o)

###############################################################################
# Recipes
###############################################################################

all: $(MAIN_OBJ) $(MAIN_OBJS) $(PROG)

# builds for testing
test: $(MAIN_OBJS) $(TEST_OBJS) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJS) $(TEST_OBJS) -o testModel $(LINKFLAGS)
	./testModel

# builds the main program
$(PROG): $(MAIN_OBJ) $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(MAIN_OBJ) $(MAIN_OBJS) -o $@ $(LINKFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(MAIN_SRC) $(MAIN_SRCS) $(TEST_SRCS)

clean:
	rm -f *.bak $(MAIN_OBJ) $(MAIN_OBJS) $(TEST_OBJS) core.* $(PROG)
