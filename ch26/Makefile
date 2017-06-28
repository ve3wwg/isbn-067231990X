# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall -DHAVE_SEMUN -g
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= pagesize messages mprotect madvise

all:    $(TARGETS)

pagesize:  pagesize.o
	$(CC) -o pagesize pagesize.o

messages:  messages.o
	$(CC) -o messages messages.o

mprotect:  mprotect.o
	$(CC) -o mprotect mprotect.o

madvise:  madvise.o
	$(CC) -o madvise madvise.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
