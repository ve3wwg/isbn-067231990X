# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -Wall

.c.o:
	$(CC) $(CCOPTS) $<

.o:
	$(CC) $< -o $*

TARGETS= lockfile

all:    $(TARGETS)

lockfile: lockfile.o
	$(CC) lockfile.o -o lockfile

clean:  cleanfiles
	rm -f *.o core a.out sparse.dat file.dat file.lck

clobber: clean
	rm -f $(TARGETS)

cleanfiles:
	rm -f file.dat file.lck
