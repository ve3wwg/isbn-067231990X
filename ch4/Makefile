# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -Wall

.c.o:
	$(CC) $(CCOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= umask unixio sparse sync writev tty

all:    $(TARGETS)

umask:  umask.o
	$(CC) umask.o -o umask

unixio: unixio.o
	$(CC) unixio.o -o unixio

sparse: sparse.o
	$(CC) sparse.o -o sparse

sync:   sync.o
	$(CC) sync.o -o sync

writev: writev.o
	$(CC) writev.o -o writev

tty:    tty.o
	$(CC) tty.o -o tty

clean:
	rm -f *.o core a.out sparse.dat

clobber: clean
	rm -f $(TARGETS)
