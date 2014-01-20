# for shared types file
INCFLAGS = -I ../include
# for vecmath
INCFLAGS += -I ../vecmath/include
# for boost
INCFLAGS += -I /usr/local/include
# for openGL
INCFLAGS += -I /usr/include/GL

# Linux on linux, Darwin on mac
SYSTEM = $(shell uname -s)

# mac and linux use different LINKFLAGS when working with openGL
ifeq ($(SYSTEM), Linux)
LINKFLAGS = -L. -lRK4 -lglut -lGL -lGLU
else ifeq ($(SYSTEM), Darwin)
LINKFLAGS = -L. -framework GLUT -framework OpenGL -framework Cocoa
endif

# there are two programs available here. One is the interactive visualizer and
# one is the static imager. This specifies the main files and executable names
# to be used with each
INTER_PROG = visualizer
STATIC_PROG = imager
INTER_MAIN = interactive.cpp
INTER_OBJ = $(INTER_MAIN:.cpp=.o)
STATIC_MAIN = static.cpp
STATIC_OBJ = $(STATIC_MAIN:.cpp=.o)

CC = g++
CFLAGS = -g -Wall -ansi -arch x86_64
ALL_SRCS = $(wildcard *.cpp)
ALL_SRCS += $(wildcard ../vecmath/src/*.cpp)

# filter out the main files from the sources
SRCS = $(filter-out $(INTER_MAIN) $(STATIC_MAIN), $(ALL_SRCS))

# find all object files
OBJS = $(SRCS:.cpp=.o)

###############################################################################
# Recipes
###############################################################################

all: $(OBJS) $(INTER_PROG) $(STATIC_PROG)

# builds the interactive visualizer
$(INTER_PROG): $(OBJS) $(INTER_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(INTER_OBJ) -o $@ $(LINKFLAGS)

# builds the static visualizer
$(STATIC_PROG): $(OBJS) $(STATIC_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(STATIC_OBJ) -o $@ $(LINKFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(ALL_SRCS)

clean:
	rm -f *.bak $(OBJS) $(INTER_OBJ) $(STATIC_OBJ) core.* $(INTER_PROG) $(STATIC_PROG)
