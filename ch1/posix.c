/* posix.c */

#include <stdio.h>
#include <unistd.h>

int
main(int argc,char **argv) {

    (void) argc;
    (void) argv;

#ifdef _POSIX_SOURCE
    printf("_POSIX_SOURCE = %ld\n",(long)_POSIX_SOURCE);
#endif

#ifdef _POSIX_C_SOURCE
    printf("_POSIX_C_SOURCE = %ld\n",(long)_POSIX_C_SOURCE);
#endif

#ifdef _POSIX_VERSION
    printf("_POSIX_VERSION = %ld\n",(long)_POSIX_VERSION);
#endif

    return 0;
}
