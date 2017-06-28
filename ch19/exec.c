/* exec.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
 * If the ps(1) command is not located at /bin/ps on your system,
 * then change the pathname defined for PS_PATH below.
 */
#define PS_PATH "/bin/ps"       /* PS(1) */

extern char **environ;          /* Our environment */

/*
 * EXEC(2) the PS(1) Command :
 */
static void
exec_ps_cmd(void) {
    static char *argv[] = { "ps", "-l", NULL };

    /*
     * Exec the ps command: ps f
     */
    execve(PS_PATH,argv,environ);

    /*
     * If control reaches here, then the execve(2)
     * call has failed!
     */
    fprintf(stderr,"%s: execve(2)\n",strerror(errno));
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    pid_t pid;          /* Process ID of the child process */
    pid_t wpid;         /* Process ID from wait() */
    int status;         /* Exit status from wait() */

    /*
     * First create a new child process :
     */
    pid = fork();

    if ( pid == -1 ) {
        /*
         * Fork failed to create a process :
         */
        fprintf(stderr,"%s: Failed to fork()\n",strerror(errno));
        exit(13);

    } else if ( pid == 0 ) {
        /*
         * This is the child process running :
         */
        exec_ps_cmd();          /* Start the ps command */

    }

    /*
     * This is the parent process running :
     */
    printf("PID %ld: Started child PID %ld.\n",
        (long)getpid(),     /* Our PID */
        (long)pid);         /* Child's PID */

    /*
     * Wait for the child process to terminate :
     */
    wpid = wait(&status);   /* Child's exit status */
    if ( wpid == -1 ) {
        /*
         * The wait() call failed :
         */
        fprintf(stderr,"%s: wait(2)\n",strerror(errno));
        return 1;

    } else if ( wpid != pid ) {
        /* Should never happen in this program: */
        abort();
    }

    /*
     * The child process has terminated:
     */
    if ( WIFEXITED(status) ) {
        /*
         * Normal exit -- print status
         */
        printf("Exited: $? = %d\n",WEXITSTATUS(status));

    } else if ( WIFSIGNALED(status) ) {
        /*
         * Process abort, kill or signal:
         */
        printf("Signal: %d%s\n",
            WTERMSIG(status),
            WCOREDUMP(status) ? " with core file." : "");

    } else {
        /*
         * Stopped child process :
         */
        puts("Stopped child process.");
    }

    return 0;
}
