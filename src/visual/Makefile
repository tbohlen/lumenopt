# for shared types file
INCFLAGS = -I ../../include
INCFLAGS += -I .
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
VISUAL_PROG = visualizer
IMAGER_PROG = imager
VISUAL_MAIN = visualizer-main.cpp
VISUAL_OBJ = $(VISUAL_MAIN:.cpp=.o)
IMAGER_MAIN = imager.cpp
IMAGER_OBJ = $(IMAGER_MAIN:.cpp=.o)

CC = g++
CFLAGS = -g -Wall -ansi -arch x86_64
ALL_SRCS = $(wildcard *.cpp)
ALL_SRCS += $(wildcard ../vecmath/*.cpp)

# filter out the main files from the sources
SRCS = $(filter-out $(VISUAL_MAIN) $(IMAGER_MAIN), $(ALL_SRCS))

# find all object files
OBJS = $(SRCS:.cpp=.o)

###############################################################################
# Recipes
###############################################################################

all: $(OBJS) $(VISUAL_PROG) $(IMAGER_PROG)

# builds the interactive visualizer
$(VISUAL_PROG): $(OBJS) $(VISUAL_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(VISUAL_OBJ) -o $@ $(LINKFLAGS)

# builds the imager visualizer
$(IMAGER_PROG): $(OBJS) $(IMAGER_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(IMAGER_OBJ) -o $@ $(LINKFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(INCFLAGS)

depend:
	makedepend $(INCFLAGS) -Y $(ALL_SRCS)

clean:
	rm -f *.bak $(OBJS) $(VISUAL_OBJ) $(IMAGER_OBJ) core.* $(VISUAL_PROG) $(IMAGER_PROG)
