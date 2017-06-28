# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= regexpr

all:    $(TARGETS)

regexpr:  regexpr.o
	$(CC) -o regexpr regexpr.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
