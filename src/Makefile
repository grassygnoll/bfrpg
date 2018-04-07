# make depend (NOTE* can't get this to work)
# make
# make all
# make clean

# Define compiler (gcc = C; g++ = C++)
CC=gcc

# Define compiler flags desired (this is for Debug version)
CFLAGS = -Wall -g

# Compiler flag for production release version
#CFLAGS = -Wall -O2

# Define includes
INCLUDES = -I./

# Define additional library paths:
LFLAGS = -L./

# Define libraries to link in (i.e. *.so or *.a files)
LIBS =

# Define C source files to compile
SRCS = testdrvr.c exp.c util.c

# Define the object files
OBJS = $(SRCS:.c=.o)

# Define the executable file
MAIN = ../testExp

# Rules to build:

.PHONY: depend clean

all: $(MAIN)
	@echo testExp has been compiled

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
clean:
	$(RM) *.o *~ core $(MAIN)

#depend: $(SRCS)
#	makedepend $(INCLUDES) $^

# DO NOT DELETE THIS LINE -- make depend needs it
