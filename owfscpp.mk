#
#	Makefile de owfscpp
#

GCCVERSIONGTEQ47 := $(shell expr `gcc -dumpversion | cut -f2 -d.` \>= 7)

ifeq "$(GCCVERSIONGTEQ4)" "1"
    CFLAGS = -std=c++11 -fsanitize=address -Wzero-as-null-pointer-constant
else
    CFLAGS = -std=c++0x
endif

ifeq ($(mode),debug)
  CFLAGS += -O0 -g -ggdb3 -Wall -Wextra -pedantic -pedantic-errors -Wmain -Weffc++ -Wswitch-default -Wswitch-enum -Wmissing-declarations -Wunreachable-code -Wfloat-equal -Wundef -Wredundant-decls -Winit-self -Wshadow -Wnon-virtual-dtor
else
  CFLAGS += -O2 -s 
endif

CFLAGS+= -DLINUX -Isrc  
LDFLAGS=-lm

VPATH = src:test:examples
OBJS_test = owfscpp.o SimpleSock.o SafeFunctions.o main.o
OBJS_example1  = owfscpp.o SimpleSock.o SafeFunctions.o example1.o
OBJS_example2  = owfscpp.o SimpleSock.o SafeFunctions.o example2.o
OBJS_example3  = owfscpp.o SimpleSock.o SafeFunctions.o example3.o

all:	    unittest example1 example2 example3

unittest: $(OBJS_test)
	        g++ -o $@ $(OBJS_test) $(CFLAGS) $(LDFLAGS)
example1: $(OBJS_example1)
	        g++ -o $@ $(OBJS_example1) $(CFLAGS) $(LDFLAGS)
example2: $(OBJS_example2)
	        g++ -o $@ $(OBJS_example2) $(CFLAGS) $(LDFLAGS)
example3: $(OBJS_example3)
	        g++ -o $@ $(OBJS_example3) $(CFLAGS) $(LDFLAGS)

clean:
	    rm -f unittest example1 example2 example3 $(OBJS_test)

.cpp.o:
	    g++ $(CFLAGS) -c $<