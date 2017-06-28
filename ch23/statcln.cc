// statcln.cc :

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "msq.h"
#include "statmsg.h"

int
main(int argc,char **argv) {
    int x;
    Msq q;                      // Message queue object
    StatMsg m;                  // Message buffer
    size_t msz;                 // Message size
    char *pathname;             // Pathname to query

    (void) argc;
    (void) argv;

    /*
     * Access the queue :
     */
    try {
        q.access(0xFEEDF00D);
    } catch ( int e ) {
        errno = e;
        perror("Accessing statsrv queue");
    }

    /*
     * Issue server requests for each command line
     * argument. If the argument starts with '$', then
     * request a lstat(2) instead of stat(2) :
     */
    for ( x=1; x<argc; ++x ) {
        /*
         * Form the server request :
         */
        if ( !strcasecmp(argv[x],"STOP") )
            // STOP SERVER REQUEST :
            m.request = StatMsg::stop;
        else {
            // STAT(2) or LSTAT(2) REQUEST :
            if ( argv[x][0] == '$' ) {
                m.request = StatMsg::lstat;
                pathname = argv[x] + 1;   // Skip '$'
            } else {
                m.request = StatMsg::stat;
                pathname = argv[x];       // Pathname
            }
            strncpy(m.u.path,pathname,sizeof m.u.path);
        }

        /*
         * Initialize other message components :
         */
        m.error = 0;                    // Clear
        m.PID = getpid();               // Our process ID
        m.msgtyp = 1;                   // Send to the server

        /*
         * Send the request to the server :
         */
        try {
            q.send(m,sizeof m);         // Send the message
        } catch ( int e ) {
            errno = e;
            perror("s.send()");
            return 1;                   // Bail out
        }

        /*
         * If the request is to stop, then exit loop :
         */
        if ( m.request == StatMsg::stop )
            break;                      // There will be no reply

        /*
         * Wait for the response :
         */
        try {
            q.recv(m,msz,sizeof m,getpid(),0);
        } catch ( int e ) {
            errno = e;
            perror("Receiving from queue");
            return 1;
        }

        /*
         * Report response :
         */
        printf("RESPONSE %14s :  ",pathname);

        if ( m.error != 0 )
            printf(" ERROR: %s\n",strerror(m.error));
        else
            printf(" SIZE:  %ld bytes\n",(long)m.u.stbuf.st_size);
    }

    /*
     * Exit client program :
     */
    q.dispose();                        // Reset object
    return 0;
}

// End statcln.cc
