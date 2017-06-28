#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int sys_nerr;    /* Highest supported error code */

int
main(int argc,char **argv) {
    int x;
    static int ecodes[] = { -1, EIO, 0 };

    /* Get maximum code and add 4096 */
    ecodes[2] = sys_nerr + 4096;    /* A very high code */

    for ( x=0; x<3; ++x ) {
        errno = ecodes[x];
        printf("%4d = '%s'\n",ecodes[x],strerror(errno));
    }

    return 0;
}
