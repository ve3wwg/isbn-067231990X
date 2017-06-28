/* ctlget.c */

#include "semop.h"

void
ctl_get(int optch,int cmd,int semx) {
    int z;
    union semun un;

    z = semctl(semid,semx,cmd,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c %d\n",
            strerror(errno),
            optch,
            semx);
        exit(1);
    }

    printf("  -%c %d => %d\n",optch,semx,z);
    fflush(stdout);
}
