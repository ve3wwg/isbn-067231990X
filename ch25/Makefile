# Makefile

# For BSD:
# STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall -DHAVE_SEMUN -g
CX=     cc
CXOPTS= -c $(STD) -Wall -fhandle-exceptions

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJS=   globat.o globcr.o globget.o globlk.o globset.o \
        globvar.o globdest.o globun.o

TARGETS= globvar

all:    $(TARGETS)

globvar:  $(OBJS)
	$(CC) -o globvar $(OBJS)

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
