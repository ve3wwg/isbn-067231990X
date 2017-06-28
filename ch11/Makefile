# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall
CX=     cc
CXOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJ=    gettime.o ctime.o asctime.o localtime.o mktime.o strftime.o main.o

TARGETS= dtime

all:    $(TARGETS)

dtime:  $(OBJ)
	$(CC) -o dtime $(OBJ) -lstdc++

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)

