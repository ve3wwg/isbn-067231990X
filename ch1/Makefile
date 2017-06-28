# Makefile

# For BSD:
STD=_POSIX_C_SOURCE=199309L

CCOPTS= -c -D$(STD) -Wall

.c.o:
	$(CC) $(CCOPTS) $<

all:
	@echo "All programs in this directory must be compiled"
	@echo "individually according to the commands shown in"
	@echo "the book. The only useful targets in this Makefile"
	@echo "is 'clobber' for cleaning up the directory."

clean:
	rm -f *.o core a.out

clobber: clean
