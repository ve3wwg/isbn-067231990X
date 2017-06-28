/* report.c */

#include "semop.h"

/*
 * Report SEM_UNDO status :
 */
void
report(int optch,key_t key,int flags[]) {
    int x;

    if ( optch == 'R' ) {
        /*
         * This report only performed for -R option :
         */
        printf("  -%c : key    0x%08lX\n",optch,(long)key);
        printf("  -%c : IPC ID %d\n",optch,semid);
    }

    for ( x=0; x<n_sem; ++x )
        printf("  -%c : %d %s SEM_UNDO\n",
            optch,
            x,
            flags[x] & SEM_UNDO ? "uses" : "has no");
            fflush(stdout);
    fflush(stdout);
}
