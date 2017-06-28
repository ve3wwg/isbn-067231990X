/* semsetval.c */

#include "semop.h"

void
ctl_setval(int optch,int semx,int value) {
    int z;
    union semun un;

    un.val = value;
    z = semctl(semid,semx,SETVAL,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c %d=%d\n",
            strerror(errno),optch,semx,value);
        exit(1);
    }

    printf("  -%c %d=%d\n",optch,semx,value);
    fflush(stdout);
}
