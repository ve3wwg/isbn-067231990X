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

TARGETS= popen pmail smail

all:    $(TARGETS)

popen:  popen.o
	$(CC) -o popen popen.o

pmail:  pmail.o
	$(CC) -o pmail pmail.o

smail:  smail.o
	$(CC) -o smail smail.o

clean:  
	rm -f *.o core *.core a.out 

clobber: clean
	rm -f $(TARGETS)
