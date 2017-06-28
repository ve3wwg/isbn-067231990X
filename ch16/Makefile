# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall -g
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= nblockio select poll

all:    $(TARGETS)

nblockio: fifo nblockio.o
	$(CC) -o nblockio nblockio.o

select: select.o
	$(CC) -o select select.o

poll:   poll.o
	$(CC) -o poll poll.o

fifo:
	mkfifo ./fifo 

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS) ./fifo
