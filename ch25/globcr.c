/* globcr.c */

#include "globvar.h"

/*
 * Create a new shared memory variable pool :
 */
void
create_vars(int shm_size) {
    int z;                      /* Status code */
    int semid;                  /* Semaphore IPC ID */
    int offset;                 /* Byte offset */
    union semun un;             /* Union of semctl() args */
    struct shmid_ds shminfo;    /* Shared memory info */

    /*
     * Create shared memory region :
     */
    z = shmget(IPC_PRIVATE,shm_size,IPC_CREAT|0600);

    if ( z == -1 ) {
        fprintf(stderr,"%s: shmmget(,%d,IPC_CREAT)\n",
            strerror(errno),shm_size);
        exit(1);
    }

    shmid = z;                  /* IPC ID */

    /*
     * Create semaphore for this region :
     */
    z = semget(IPC_PRIVATE,1,IPC_CREAT|0600);

    if ( z == -1 ) {
        fprintf(stderr,"%s: semget(,IPC_CREAT)\n",strerror(errno));
        exit(1);
    }

    semid = z;                  /* IPC ID */

    /*
     * Discover the actual size of the region :
     */
    z = shmctl(shmid,IPC_STAT,&shminfo);

    if ( z == -1 ) {
        fprintf(stderr,"%s: shmctl(%d,IPC_STAT)\n",
            strerror(errno),shmid);
        exit(1);
    }

    shm_size = shminfo.shm_segsz;   /* Actual size of the memory region */

    /*
     * Initialize binary semaphore to value of 1 :
     */
    un.val = 1;

    z = semctl(semid,0,SETVAL,un.val);

    if ( z == -1 ) {
        fprintf(stderr,"%s: semctl(%d,0,SETVAL)\n",
            strerror(errno),semid);
        exit(1);
    }

    /*
     * Attach shared memory, and initialize it :
     */
    attach_vars();              /* Attach shared memory */
    globvars->semid = semid;    /* Place semaphore ID into shared memory */

    offset = (int) ( &globvars->vars[0] - (char *)globvars );
    globvars->size = shm_size - offset;
    globvars->vars[0] = globvars->vars[1] = 0;
}
