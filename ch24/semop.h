/* semop.h */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef HAVE_SEMUN              /* Does sys/sem.h define this? */

union semun {
    int     val;                /* Value */
    struct  semid_ds *buf;      /* IPC_STAT info */
    u_short *array;             /* Array of values */
};

#endif

#define MAX_NSET    16          /* Max value for n_sem */

extern int semid;               /* Semaphore IPC ID */
extern int n_sem;               /* # of semaphores to a set */
extern struct semid_ds sembuf;  /* The last IPC_STAT info */

extern void get_set(int optch,key_t key,int createflg);
extern void ctl_semop(int optch,const char *optarg,
    int sems[],int array[],int flags[],int n);
extern void ctl_stat(int optch,int rptflag);
extern void ctl_chmod(int optch,mode_t mode);
extern void ctl_chown(int optch,const char *user_id);
extern void ctl_chgrp(int optch,const char *group);
extern void ctl_rmid(int optch);
extern void ctl_getval(int optch,int semx);
extern void ctl_getall(int optch);
extern void ctl_setval(int optch,int semx,int value);
extern void ctl_setall(int optch,int array[]);
extern void ctl_get(int optch,int cmd,int semx);

extern void usage(void);
extern int cvt2ulong(const char *str,unsigned long *ulp);
extern int cvt2array(const char *str,int array[],const char *delim);
extern int cvt2semops(const char *str,int sems[],int array[],int flags[]);
extern void report(int optch,key_t key,int flags[]);

/* End semop.h */
