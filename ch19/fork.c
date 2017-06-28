/* fork.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int
main(int argc,char **argv) {
    pid_t pid;              /* Process ID of the child process */

    pid = fork();           /* Create a new child process */

    if ( pid == (pid_t)(-1) ) {
        fprintf(stderr,"%s: Failed to fork()\n",strerror(errno));
        exit(13);

    } else if ( pid == 0 ) {
        printf("PID %ld: Child started, parent is %ld.\n",
            (long)getpid(),     /* Current child PID */
            (long)getppid());   /* Parent PID */

    } else  {
        printf("PID %ld: Started child PID %ld.\n",
            (long)getpid(),     /* Current parent PID */
            (long)pid);         /* Child's PID */
    }

    sleep(1);                   /* Wait one second */
    return 0;
}
