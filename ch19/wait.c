/* wait.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(int argc,char **argv) {
    pid_t pid;              /* Process ID of the child process */
    pid_t wpid;             /* Process ID from wait(2) */
    int status;             /* Status code from wait(2) */

    pid = fork();           /* Create a new child process */

    if ( pid == (pid_t)(-1) ) {
        fprintf(stderr,"%s: Failed to fork()\n",strerror(errno));
        exit(13);

    } else if ( pid == 0 ) {
        printf("PID %ld: Child started, parent is %ld.\n",
            (long)getpid(),     /* Current child PID */
            (long)getppid());   /* Parent PID */
        return 0;               /* Child process just exits */

    }

    /*
     * Parent process :
     */
    printf("PID %ld: Started child PID %ld.\n",
        (long)getpid(),     /* Current parent PID */
        (long)pid);         /* Child's PID */

    /*
     * Wait for the child process to exit, and obtain
     * its termination status :
     */
    wpid = wait(&status);   /* Wait for child process to exit */
    if ( wpid == (pid_t)(-1) )
        perror("wait(2)");  /* Report wait(2) error */

    /*
     * There should be no trace of the child process in
     * this particular display :
     */
    system("ps -l");        /* List the processes */
    
    return 0;
}
