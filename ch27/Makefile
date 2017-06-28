# Makefile

# For BSD:
#STD=-D_POSIX_C_SOURCE=199309L -D_POSIX_SOURCE

CCOPTS= -c $(STD) -Wall -I/usr/X11R6/include
XLIBS=-L/usr/X11R6/lib -lX11

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJS=   xeg.o events.o

TARGETS= xeg

all:    $(TARGETS)

xeg:    $(OBJS)
	$(CC) -o xeg $(OBJS) $(XLIBS)

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS) 
