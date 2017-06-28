/* globat.c */

#include "globvar.h"

/*
 * Attach the shared variable pool :
 */
void
attach_vars(void) {

    /*
     * Attach shared memory region :
     */
    globvars = (GlobVars *)shmat(shmid,0,0);

    if ( (void *)(globvars) == (void *)(-1) ) {
        fprintf(stderr,"%s: shmat(%d,0,0)\n",strerror(errno),shmid);
        exit(1);
    }
}
