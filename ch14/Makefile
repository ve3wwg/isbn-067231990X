# Makefile

# For BSD:
#STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJS=   Dir.o Dbm.o InoDb.o
TARGETS= SnapShot EmptyDb

all:    $(TARGETS)

SnapShot: $(OBJS) SnapShot.o
	$(CC) -o SnapShot SnapShot.o $(OBJS) -lstdc++

EmptyDb: $(OBJS) EmptyDb.o
	$(CC) -o EmptyDb EmptyDb.o $(OBJS) -lstdc++

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS) snapshot.db
