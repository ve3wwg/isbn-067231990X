/* ursig1.c */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int count = 0;

void
handler(int signo) {

	if ( ++count < 3 )
   	    signal(SIGINT,handler); /* Re-instate handler */
    else
        signal(SIGINT,SIG_DFL); /* Revert to default */
	write(1,"Got SIGINT\n",11); /* Write message */
}

int
main(int argc,char **argv) {

	signal(SIGINT,handler);     /* Register function */

	for (;;) {
		sleep(4);               /* Snooze */
		puts("Waiting for SIGINT..");
	}	
	return 0;
}
