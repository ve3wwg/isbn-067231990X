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

TARGETS= fork zombie wait exec

all:    $(TARGETS)

fork:  fork.o
	$(CC) -o fork fork.o

zombie:  zombie.o
	$(CC) -o zombie zombie.o

wait:  wait.o
	$(CC) -o wait wait.o

exec:  exec.o
	$(CC) -o exec exec.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
