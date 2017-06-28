/* ctlsem.c */

#include "semop.h"

void
ctl_semop(
  int optch,
  const char *optarg,
  int sems[],
  int array[],
  int flags[],
  int n) {
    int z;
    int x;                                  /* Iterator */
    int semx;                               /* Semaphore number */
    struct sembuf ops[MAX_NSET];

    for ( x=0; x<n; ++x ) {
        ops[x].sem_num = semx = sems[x];    /* Semaphore # */
        ops[x].sem_op = array[x];           /* Semaphore operation */
        if ( semx >= 0 && semx < n_sem )
            ops[x].sem_flg = semx < n_sem   /* In range ? */
                ? flags[semx]               /* Semaphore flags */
                : 0;                        /* else use zero */
    }

    z = semop(semid,ops,n);
    if ( z == -1 ) {
        fprintf(stderr,"%s: -%c %s\n",strerror(errno),optch,optarg);
        exit(1);
    }

    printf("  -%c %s =>",optch,optarg);

    for ( x=0; x<n; ++x )
        printf(" {%d,%+d,%s}",
            ops[x].sem_num,
            ops[x].sem_op,
            ops[x].sem_flg ? "SEM_UNDO" : "0");
    putchar('\n');

    fflush(stdout);
}
