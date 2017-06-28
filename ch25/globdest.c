/* globdest.c */

#include "globvar.h"

/*
 * Destroy the shared memory variable pool :
 */
void
destroy_vars(void) {
    int z;                      /* Status code */
    int semid;                  /* Semaphore IPC ID */
    union semun un;             /* Union of semctl() args */
    
    /*
     * Lock the shared memory region :
     */
    glob_lock();
    semid = globvars->semid;    /* Semaphore IPC ID */
    
    /*
     * Destroy locking semaphore :
     */
    z = semctl(semid,0,IPC_RMID,un);

    if ( z == -1 ) {
        fprintf(stderr,"%s: semctl(%d,0,IPC_RMID)\n",
            strerror(errno),semid);
        exit(1);
    }

    /*
     * Detach shared memory :
     */
    z = shmdt(globvars);

    if ( z == -1 ) {
        fprintf(stderr,"%s: shmdt(2)\n",strerror(errno));
        exit(1);
    }

    /*
     * Destroy shared memory :
     */
    z = shmctl(shmid,IPC_RMID,NULL);

    if ( z == -1 ) {
        fprintf(stderr,"%s: shmctl(%d,IPC_RMID)\n",
            strerror(errno),shmid);
        exit(1);
    }
}
