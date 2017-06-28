/* pmail.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int
main(int argc,char **argv) {
    struct passwd *pw = 0;      /* Password info */
    char cmd[256];              /* Command buffer */
    FILE *p = 0;                /* mailx pipe */

    /*
     * Lookup our userid:
     */
    if ( !(pw = getpwuid(geteuid())) ) {
        perror("getpwuid()");
        return 13;
    }

    /*
     * Format command :
     */
    sprintf(cmd,"mail -s 'A message from process ID %ld' %s",
        (long)getpid(),         /* Process ID */
        pw->pw_name);           /* User name */

    /*
     * Open a pipe to mailx:
     */
    if ( !(p = popen(cmd,"w")) ) {
        perror("popen(3)");
        return 13;
    }

    /*
     * Now write our message:
     */
    fprintf(p,"This is command %s speaking.\n",argv[0]);
    fprintf(p,"I am operating in the account for %s\n",pw->pw_gecos);

    if ( getuid() != 0 ) {
        fprintf(p,"I'd like to operate in root instead.\n");
        fprintf(p,"I could do more damage there. :)\n\n");
    } else {
        fprintf(p,"I'd like to operate in a non-root ID instead.\n");
        fprintf(p,"I would be safer there.\n");
    }

    fprintf(p,"Sincerely,\n  Process ID %ld\n",(long)getpid());

    if ( pclose(p) == -1 ) {
        perror("pclose(3)");
        return 13;
    }

    printf("Message sent to %s\n",pw->pw_name);
    return 0;
}
