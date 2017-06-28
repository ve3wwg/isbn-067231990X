# Makefile

# For BSD:
STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= ursig1 rsig1 intalrm

all:    $(TARGETS)

ursig1: ursig1.o
	$(CC) -o ursig1 ursig1.o

rsig1: rsig1.o
	$(CC) -o rsig1 rsig1.o

intalrm: intalrm.o
	$(CC) -o intalrm intalrm.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS) 
