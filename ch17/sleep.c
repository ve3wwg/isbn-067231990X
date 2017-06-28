/* sleep.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int
main(int argc,char **argv) {
    time_t dt;

    time(&dt);
    printf("%s begun at:\t%s",__FILE__,ctime(&dt));

    puts("Zzz...(5 seconds)...");
    sleep(5);

    time(&dt);
    printf("%s completed at:\t%s",__FILE__,ctime(&dt));
    return 0;
}
