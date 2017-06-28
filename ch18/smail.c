/* smail.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <sys/types.h>

int
main(int argc,char **argv) {
    struct passwd *pw = 0;      /* Password info */
    char cmd[256];              /* Command buffer */
    int rc;                     /* Command return code */

    /*
     * Lookup our userid:
     */
    if ( !(pw = getpwuid(geteuid())) ) {
        fprintf(stderr,"%s: unknown userid\n",strerror(errno));
        return 13;
    }

    /*
     * Format command :
     */
    sprintf(cmd,"ps -l|mail -s 'PID %ld' %s",
        (long) getpid(),    /* Process ID */
        pw->pw_name);       /* User name */

    /*
     * Run the command :
     */
    errno = 0;              /* Clear errno */
    rc = system(cmd);       /* Execute the command */

    if ( rc == 127 && errno != 0 ) {
        /* Command failed to start */
        fprintf(stderr,"%s: starting system(%s)\n",
            strerror(errno),cmd);
    } else if ( rc == -1 ) {
        /* Other errors occurred */
        fprintf(stderr,"%s: system(%s)\n",
            strerror(errno),cmd);
    } else {
        printf("Command '%s'\n  returned code %d\n",cmd,rc);
        puts("Check your mail.");
    }

    return 0;
}
