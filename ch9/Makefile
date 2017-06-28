# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall -g
CX=     cc
CXOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= getopt xmt

all:    $(TARGETS)

getopt: getopt.o
	$(CC) getopt.o -o getopt

xmt: xmt.o
	$(CC) xmt.o -o xmt

clean:  
	rm -f *.o core a.out 

clobber: clean
	rm -f $(TARGETS)

