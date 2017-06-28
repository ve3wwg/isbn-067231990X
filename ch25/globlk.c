/* globlk.c */

#include "globvar.h"

static struct sembuf wait = { 0, -1, SEM_UNDO };
static struct sembuf notify = { 0, +1, SEM_UNDO };

/*
 * Perform a semaphore operation :
 */
static void
do_semop(struct sembuf *op) {
    int z;                      /* status code */

    do  {
        z = semop(globvars->semid,op,1);
    } while ( z == -1 && errno == EINTR );

    if ( z ) {
        fprintf(stderr,"%s: semop(2)\n",strerror(errno));
        exit(1);
    }
}

/*
 * Wait on semaphore to lock shared memory :
 */
void
glob_lock(void) {

    do_semop(&wait);
}

/*
 * Notify semaphore to unlock shared memory :
 */
void
glob_unlock(void) {

    do_semop(&notify);
}

