/* semsetall.c */

#include "semop.h"

void
ctl_setall(int optch,int array[]) {
    int z;
    int x;
    u_short ua[MAX_NSET];
    union semun un;
    
    for ( x=0; x<n_sem; ++x )
        ua[x] = (u_short)array[x];

    un.array = &ua[0];
    z = semctl(semid,0,SETALL,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c %d,%d,%d\n",
            strerror(errno),optch,array[0],array[1],array[2]);
        exit(1);
    }

    printf("  -%c %d,%d,%d\n",optch,array[0],array[1],array[2]);
    fflush(stdout);
}
