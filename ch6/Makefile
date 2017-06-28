# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall
CX=     cc
CXOPTS= -c -D$(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= stat pathconf

all:    $(TARGETS)

stat:   stat.o
	$(CX) stat.o -o stat -lstdc++

pathconf: pathconf.o
	$(CC) pathconf.o -o pathconf

clean:  
	rm -f *.o core a.out 

clobber: clean
	rm -f $(TARGETS)

