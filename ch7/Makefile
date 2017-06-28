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

TARGETS= readdir scandir chroot

all:    $(TARGETS)

readdir: readdir.o
	$(CC) readdir.o -o readdir

scandir: scandir.o
	$(CC) scandir.o -o scandir

chroot: chroot.o
	$(CC) chroot.o -o chroot

clean:  
	rm -f *.o core a.out 

clobber: clean
	rm -f $(TARGETS)

