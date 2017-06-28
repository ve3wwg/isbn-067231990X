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

TARGETS= tmpnam tmpnam2 mkstemp tmpfile tempnam atexit destruct

all:    $(TARGETS)

tmpnam: tmpnam.o
	$(CC) tmpnam.o -o tmpnam

tmpnam2: tmpnam2.o
	$(CC) tmpnam2.o -o tmpnam2

mkstemp: mkstemp.o
	$(CC) mkstemp.o -o mkstemp

tmpfile: tmpfile.o
	$(CC) tmpfile.o -o tmpfile

tempnam: tempnam.o
	$(CC) tempnam.o -o tempnam

atexit: atexit.o
	$(CC) atexit.o -o atexit

destruct: destruct.o
	$(CC) destruct.o -o destruct -lstdc++

clean:  
	rm -f *.o core a.out 

clobber: clean
	rm -f $(TARGETS)
	@if [ -d ./my_tmp ] ; then chmod 700 ./my_tmp 2>/dev/null ; fi
	rm -fr ./my_tmp
