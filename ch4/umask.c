/* umask.c */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

mode_t
query_umask(void) {
    mode_t old_umask;

    umask(old_umask = umask(0));
    return old_umask;
}

int
main(int argc,char **argv) {

    printf("umask = %04o\n",query_umask());
    return 0;
}
