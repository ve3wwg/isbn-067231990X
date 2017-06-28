# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall
CX=     cc
CXOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= sscanf strtol radix

all:    $(TARGETS)

sscanf: sscanf.o
	$(CC) sscanf.o -o sscanf

strtol: strtol.o
	$(CC) strtol.o -o strtol

radix: radix.o
	$(CC) radix.o -o radix

clean:  
	rm -f *.o core a.out 

clobber: clean
	rm -f $(TARGETS)

