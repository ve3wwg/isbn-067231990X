# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions
AR=     ar

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

LIBOBJ= msqveri.o msqcr.o msqac.o msqdest.o msqstat.o msqchg.o msqsend.o msqrecv.o
TARGETS= libmsq.a statsrv statcln

all:    $(TARGETS)

libmsq.a: $(LIBOBJ)
	$(AR) r libmsq.a $(LIBOBJ)

statsrv: statsrv.o libmsq.a
	$(CC) -o statsrv statsrv.o -L. -lmsq -lstdc++

statcln: statcln.o libmsq.a
	$(CC) -o statcln statcln.o -L. -lmsq -lstdc++

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
