# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall
CX=     cc
CXOPTS= -c -D$(STD) -D_POSIX_SOURCE -Wall -fPIC -fhandle-exceptions -g

.c.o:
	$(CC) $(CCOPTS) $<

.cc.o:
	$(CX) $(CXOPTS) $<

.o:
	$(CC) $< -o $*

OBJS1=   import.o getuid.o
TARGETS= libpasswd.a getuid libshared.so libdyn001.so dlmain

all:    $(TARGETS)

libpasswd.a: $(OBJS1)
	$(AR) -r libpasswd.a $(OBJS1)

libshared.so: $(OBJS1)
	$(CC) -o libshared.so $(OBJS1) -shared

getuid: libpasswd.a main.o
	$(CC) -o getuid main.o -L$(PWD) -lpasswd -lstdc++

libdyn001.so: dyn001.o
	$(CC) -o libdyn001.so -shared dyn001.o

dlmain: dlmain.o libdyn001.so
	$(CC) -o dlmain dlmain.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)

