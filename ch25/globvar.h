/* globvar.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define GLOBVARENV  "GLOBVAR"   /* Environment variable */

typedef struct {
    int     semid;              /* Semaphore's IPC ID */
    int     size;               /* Size of the vars[] array */
    char    vars[1];            /* Start of variable storage */
} GlobVars;

extern int shmid;               /* IPC ID of shared memory region */
extern int shm_size;            /* Size of shared memory region */
extern GlobVars *globvars;      /* Shared memory region */
extern int semid;               /* IPC ID of the locking semaphore set */

extern void create_vars(int shm_size);
extern void attach_vars(void);
extern char *get_var(const char *varname);
extern void set_var(const char *varname,const char *value);
extern void destroy_vars(void);
extern void glob_lock(void);
extern void glob_unlock(void);
extern void unset_var(const char *varname);

#ifndef HAVE_SEMUN              /* Does sys/sem.h define this? */

union semun {
    int     val;                /* Value */
    struct  semid_ds *buf;      /* IPC_STAT info */
    u_short *array;             /* Array of values */
};

#endif

/* End globvar.h */
