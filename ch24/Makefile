# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall -DHAVE_SEMUN
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJS=   ctlget.o semop.o semchmod.o semget.o \
        semgetall.o semgetval.o semrmid.o \
        semsetall.o semsetval.o semstat.o usage.o \
        convrt.o report.o semchown.o main.o

TARGETS= semop

all:    $(TARGETS)

semop:  $(OBJS)
	$(CC) -o semop $(OBJS)

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
