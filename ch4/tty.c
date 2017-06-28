/* tty.c */

#include <stdio.h>
#include <unistd.h>

void
tty_info(int fd) {
    int b = isatty(fd);                 /* Test if a tty */

    printf("fd=%d %s a tty\n",fd,b?"is":"isn't");
    if ( b )
        printf("tty name is '%s'\n",ttyname(fd));
}

int
main(int argc,char **argv) {

    tty_info(0);                        /* Query standard input */
    tty_info(1);                        /* Query standard output */
    tty_info(2);                        /* Query standard error */
    return 0;
}
