/* pagesize.c */

#include <stdio.h>
#include <unistd.h>

int
main(int argc,char **argv) {

    printf("Page size is %d bytes\n",getpagesize());
    return 0;
}
