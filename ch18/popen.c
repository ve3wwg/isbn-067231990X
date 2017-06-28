/* popen.c */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc,char **argv) {
    char buf[256];                      /* Input buffer */
    FILE *p;                            /* Input pipe */

    /*
     * Open pipe to ps(1) command for reading :
     */
    p = popen("ps -l","r");

    if ( !p ) {
        perror("popen(3)");
        return 13;
    }

    /*
     * Read the output of the pipe:
     */
    while ( fgets(buf,sizeof buf,p) != 0 )
        fputs(buf,stdout);

    if ( pclose(p) ) {
        perror("pclose(3)");
        return 13;
    }

    return 0;
}
