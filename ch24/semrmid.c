/* semrmid.c */

#include "semop.h"

void
ctl_rmid(int optch) {
    int z;

    z = semctl(semid,0,IPC_RMID);
    if ( z == -1 ) {
        fprintf(stderr,"%s: semctl(semid=%d,IPC_RMID)\n",
            strerror(errno),semid);
        exit(1);
    }

    semid = -1;                 /* This resource is gone now */

    printf("  -%c\n",optch);
    fflush(stdout);
}
