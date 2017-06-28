/* semgetall.c */

#include "semop.h"

void
ctl_getall(int optch) {
    int z;
    int x;
    u_short array[MAX_NSET];
    union semun un;

    un.array = &array[0];
    z = semctl(semid,0,GETALL,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c\n",strerror(errno),optch);
        exit(1);
    }

    for ( x=0; x<n_sem; ++x )
        printf("  -%c : semaphore # %d = %u\n",optch,x,array[x]);

    fflush(stdout);
}
