// statsrv.cc :

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
    int quit = 0;               // True when stop received
    Msq q;                      // Message queue object
    StatMsg m;                  // Message buffer
    size_t msz;                 // Message size
    char pathname[256+1];       // Local copy of pathname
    msqid_ds mstat;             // Message queue info

    (void) argc;
    (void) argv;

    /*
     * Create the server message queue :
     */
    try {
        q.create(0xFEEDF00D,0600);
    } catch ( int e ) {
        errno = e;
        perror("Creating a queue");
    }

    /*
     * Obtain queue information :
     */
    try {
        q.stat(mstat);
    } catch ( int e ) {
        errno = e;
        perror("q.stat()");
    }

    printf("Queue permissions were: %04o\n",mstat.msg_perm.mode);

    /*
     * For demonstration purposes,
     * make the queue read & writable to all :
     */
    mstat.msg_perm.mode = 0666;

    try {
        q.change(mstat);
    } catch ( int e ) {
        errno = e;
        perror("q.change()");
    }

    printf("Queue permissions now : %04o\n",mstat.msg_perm.mode);

    /*
     * Server message loop :
     */
    do  {
        /*
         * Receive a message of type 1 :
         */
        try {
            q.recv(m,msz,sizeof m,1,0);
        } catch ( int e ) {
            errno = e;
            perror("Receiving from queue");
            return 1;
        }

        /*
         * Process message :
         */
        switch ( (int) m.request ) {
        case StatMsg::stat :    // stat(2) request :
            strncpy(pathname,m.u.path,sizeof pathname);
            pathname[sizeof pathname-1] = 0;
            m.error = stat(pathname,&m.u.stbuf) ? errno : 0;
            break;

        case StatMsg::lstat :   // lstat(2) request :
            strncpy(pathname,m.u.path,sizeof pathname);
            pathname[sizeof pathname-1] = 0;
            m.error = lstat(pathname,&m.u.stbuf) ? errno : 0;
            break;

        case StatMsg::stop :    // stop server :
            quit = 1;           // Stop the server
            m.error = 0;        // Ack request
            break;

        default :               // Unknown request :
            m.error = EINVAL;
        }

        /*
         * Reply to client :
         */
        m.msgtyp = m.PID;       // Reply to this process

        try {
            q.send(m,sizeof m);
        } catch ( int e ) {
            errno = e;
            perror("q.send()");
            return 1;
        }
    } while ( !quit );

    /*
     * Destroy the message queue :
     */
    q.destroy();
    return 0;
}

// End statsrv.cc
