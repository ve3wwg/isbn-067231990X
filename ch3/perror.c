#include <stdio.h>
#include <errno.h>

int
main(int argc,char **argv) {

    errno = EIO;
    perror("Test EIO Message");
    return 0;
}
