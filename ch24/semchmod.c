/* semchmod.c */

#include "semop.h"

void
ctl_chmod(int optch,mode_t mode) {
    int z;
    union semun un;

    un.buf = &sembuf;                   /* Pointer to buffer */
    sembuf.sem_perm.mode = mode;        /* Change the mode */

    z = semctl(semid,0,IPC_SET,un);     /* Change mode value */
    if ( z == -1 ) {
        fprintf(stderr,"%s: semctl(semid=%d,IPC_SET)\n",
            strerror(errno),semid);
        exit(1);
    }

    printf("  -%c 0%03o\n",optch,mode);
    fflush(stdout);
}
