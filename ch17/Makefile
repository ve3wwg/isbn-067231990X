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

TARGETS= sleep impsleep usleep nanosleep r1shot timers

all:    $(TARGETS)

sleep:  sleep.o
	$(CC) -o sleep sleep.o

impsleep:  impsleep.o
	$(CC) -o impsleep impsleep.o

usleep:  usleep.o
	$(CC) -o usleep usleep.o

nanosleep:  nanosleep.o
	$(CC) -o nanosleep nanosleep.o

r1shot: r1shot.o
	$(CC) -o r1shot r1shot.o

timers: timers.o
	$(CC) -o timers timers.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
