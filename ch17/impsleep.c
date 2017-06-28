/* impsleep.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

/*
 * Signal handler for SIGALRM :
 */
static void
h_sigalrm(int signo) {

    return;                         /* Just return */
}

/*
 * An emulated sleep(2) function :
 */
static unsigned
Sleep(unsigned seconds) {
    time_t dt0, dt1;                /* Start and end times */
    unsigned e;                     /* Elapsed seconds */
    struct sigaction old_sigalrm;   /* Old signal action */
    struct sigaction new_sigalrm;   /* New signal action */
    sigset_t nosigs;                /* The empty set */

    sigemptyset(&nosigs);           /* The empty set */

    /*
     * Establish the signal action required for SIGALRM :
     */
    new_sigalrm.sa_handler = h_sigalrm;
    sigemptyset(&new_sigalrm.sa_mask);
    new_sigalrm.sa_flags = 0;

    sigaction(SIGALRM,&new_sigalrm,&old_sigalrm);

    /*
     * Get start time, start timer, pause, and get end time :
     */
    time(&dt0);                 /* Get start time in seconds */
    alarm(seconds);             /* (re)start timer */
    sigsuspend(&nosigs);        /* Wait for any signal */
    alarm(0);                   /* Cancel timer */
    time(&dt1);                 /* Get end time in seconds */
    e = (unsigned)(dt1 - dt1);  /* Elapsed time in seconds */

    /*
     * Restore SIGALRM action, and return time remaining :
     */
    sigaction(SIGALRM,&old_sigalrm,NULL);
    if ( e >= seconds )         /* Did we use up the time? */
        return 0;               /* No time remaining.. */
    return seconds - e;         /* Return time remaining */
}

int
main(int argc,char **argv) {
    time_t dt;

    time(&dt);
    printf("%s begun at:\t%s",__FILE__,ctime(&dt));

    puts("Zzz...(5 seconds)...");
    Sleep(5);

    time(&dt);
    printf("%s completed at\t%s",__FILE__,ctime(&dt));
    return 0;
}
