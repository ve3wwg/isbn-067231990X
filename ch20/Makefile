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

TARGETS= fnmatch glob

all:    $(TARGETS)

fnmatch:  fnmatch.o
	$(CC) -o fnmatch fnmatch.o

glob:   glob.o
	$(CC) -o glob glob.o

one:    
	mkdir /tmp/one
	mkdir /tmp/one/log
	mkdir /tmp/one/two
	mkdir /tmp/one/two/log
	date >/tmp/one/log/date1.log
	date >/tmp/one/log/.date3
	date >/tmp/one/two/log/date2.log

cleantmp:
	rm -fr /tmp/one

clean:  cleantmp
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
