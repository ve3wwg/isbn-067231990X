/* usleep.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

extern int usleep(unsigned int microseconds);

static unsigned
test(unsigned usec) {                   /* Microseconds to sleep */
    unsigned Zzz = 5;                   /* Sleep time in seconds */
    long count = 0L;                    /* Interation Counter */
    unsigned avg;                       /* Average time interval */
    long sb_count = (Zzz * 1000000) / usec;
    time_t t0, t1;
    
    time(&t0);
    printf("%s started at:\t%s",__FILE__,ctime(&t0));

    for ( ; time(&t1) - t0 < Zzz; ++count ) {
        usleep(usec);
    }

    printf("%s ended at:\t%s",__FILE__,ctime(&t1));

    printf("Elapsed time is %u seconds\n",(unsigned)(t1-t0));
    printf("Counter reached %ld, should be %ld\n",count,sb_count);
    avg = (unsigned) (((long)(t1-t0))*1000000 / (long)count);
    printf("The average time was %u usec.\n",avg);

    return avg;
}

int
main(int argc,char **argv) {
    short x;
    unsigned a;
    unsigned usec = ~0U;
    unsigned usleep_times[] = {
        1000000, 100000, 10000, 1000, 100
    };

    for ( x=0; x<5; ++x ) {
        printf("TESTING USLEEP(%u) :\n",usleep_times[x]);
        a = test(usleep_times[x]);
        putchar('\n');

        if ( a < usec )
            usec = a;       /* Save shortest avg time */
    }

    printf("Shortest usleep(3) time is %u usec.\n",usec);

    return 0;
}
