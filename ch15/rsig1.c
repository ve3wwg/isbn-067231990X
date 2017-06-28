/* rsig1.c */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int count = 0;

void
handler(int signo) {

	signal(SIGINT,handler);     /* Re-instate handler */
	++count;					/* Increment count */
	write(1,"Got SIGINT\n",11); /* Write message */
}

int
main(int argc,char **argv) {
	struct sigaction sa_old;	/* Old signal actions */
	struct sigaction sa_new;	/* New signal actions */

	sa_new.sa_handler = handler;	/* Point to our function */
	sigemptyset(&sa_new.sa_mask);	/* Clear mask */
	sa_new.sa_flags = 0;			/* No special flags */
	sigaction(SIGINT,&sa_new,&sa_old);

	while ( count < 2 ) {
		puts("Waiting for SIGINT..");
		sleep(4);               /* Snooze */
	}	

	sigaction(SIGINT,&sa_old,0);	/* Restore signal actions */

	puts("End.");
	return 0;
}
