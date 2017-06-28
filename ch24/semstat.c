/* semstat.c */

#include "semop.h"

struct semid_ds sembuf;     /* Used for IPC_STAT/IPC_SET */

/*
 * Return user ID string :
 */
static char *
user_id(uid_t uid) {
    struct passwd *pw = getpwuid(uid);

    return !pw ? "?" : pw->pw_name;
}

/*
 * Return group ID string :
 */
static char *
group_id(gid_t gid) {
    struct group *gr = getgrgid(gid);

    return !gr ? "?" : gr->gr_name;
}

/*
 * Get status on semaphore set :
 */
void
ctl_stat(int optch,int reportflg) {
    int z;
    union semun un;

    un.buf = &sembuf;

    z = semctl(semid,0,IPC_STAT,un);
    if ( z == -1 ) {
        fprintf(stderr,"%s: semctl(semid=%d,IPC_STAT)\n",
            strerror(errno),semid);
        exit(1);
    }

    if ( reportflg == 1 ) {
        printf("  -%c {\n"
            "    sem_nsems = %d\n"
            "    sem_perm {\n"
            "      cuid = %d (%s)\n"
            "      cgid = %d (%s)\n",
            optch,
            (int)sembuf.sem_nsems,
            (int)sembuf.sem_perm.cuid,
            user_id(sembuf.sem_perm.cuid),
            (int)sembuf.sem_perm.cgid,
            group_id(sembuf.sem_perm.cgid));
        printf(
            "      uid  = %d (%s)\n"
            "      gid  = %d (%s)\n"
            "      mode = 0%03o\n"
            "      key  = 0x%08lX\n"
            "    };\n"
            "  };\n",
            (int)sembuf.sem_perm.uid,
            user_id(sembuf.sem_perm.uid),
            (int)sembuf.sem_perm.gid,
            group_id(sembuf.sem_perm.gid),
            (int)sembuf.sem_perm.mode & 0777,
            (long)sembuf.sem_perm.key);
        fflush(stdout);
    }

    /*
     * Check that our idea of set size agrees with actual :
     */
    if ( reportflg == -1 )          /* -a option call? */
        n_sem = sembuf.sem_nsems;   /* Yes, adjust for actual count */

    else if ( n_sem != sembuf.sem_nsems ) {
        fflush(stdout);
        fprintf(stderr,"  WARNING: # semaphores in set is %d\n",
            sembuf.sem_nsems);
        fflush(stderr);
        n_sem = sembuf.sem_nsems;   /* Adjust for actual count */
    }
}
