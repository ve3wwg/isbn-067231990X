# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -Wall

.c.o:
	$(CC) $(CCOPTS) $<

TARGETS= perror strerror

all:    $(TARGETS)

perror: perror.o
	$(CC) perror.o -o perror

strerror: strerror.o
	$(CC) strerror.o -o strerror

clean:
	rm -f *.o core a.out

clobber: clean
	rm -f $(TARGETS)
