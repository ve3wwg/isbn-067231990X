/* semgetval.c */

#include "semop.h"

void
ctl_getval(int optch,int semx) {
    int z;
    union semun un;

    z = semctl(semid,semx,GETVAL,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c %d\n",strerror(errno),optch,semx);
        exit(1);
    }

    printf("  -%c %d => %d\n",optch,semx,z);
    fflush(stdout);
}
