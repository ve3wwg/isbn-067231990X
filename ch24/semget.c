/* semget.c */

#include "semop.h"

void
get_set(int optch,key_t key,int createflg) {
    int z;
    mode_t um;
    mode_t mode;                /* Create permissions */
    int flags;                  /* semget(2) flags */

    if ( createflg )
        flags = IPC_CREAT|IPC_EXCL; /* Create set */
    else
        flags = 0;              /* Access existing set */

    um = umask(077);            /* Query umask */
    umask(um);                  /* Restore umask */
    mode = 0666 & ~um;          /* Create permissions */

    /*
     * Create a set of n_sem semaphores :
     */
    z = semget(key,n_sem,flags|mode);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c\n",strerror(errno),optch);
        exit(1);
    }

    semid = z;                  /* Semaphore IPC ID */

    printf("  -%c 0x%X => IPC ID %d\n",optch,(int)key,semid);
    if ( key == IPC_PRIVATE )
        printf("  WARNING: IPC_PRIVATE used.\n");
    fflush(stdout);
}
