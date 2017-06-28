// msqrecv.c :

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::recv :
//
// ARGUMENTS :
//  msg         The receiving buffer for the message
//  size        The returned size of the message
//  maxsz       The maximum size of the returned message
//  msgtyp      The message type to use (priority)
//  flags       Flags IPC_NOWAIT, IPC_EXCEPT and
//              IPC_NOERROR (optional)
//
// RETURNS :
//  0           No message returned (with IPC_NOWAIT)
//  1           Message was returned
//
//  This method receives a message from the message queue.
//  Object must be in a ready state.
////////////////////////////////////////////////////////////

int
Msq::recv(Msg &msg,size_t &size,size_t maxsz,long msgtyp,int flags) {
    int z;
    size_t msgsz = maxsz - sizeof msg.msgtyp;

    _verify(ready);

    do  {
        z = msgrcv(msqid,&msg,msgsz,msgtyp,flags);
    } while ( z == -1 && errno == EINTR );

    if ( z == -1 ) {
        if ( flags & IPC_NOWAIT && errno == EAGAIN )
            return 0;               // No message read
        throw error = errno;        // Error occurred
    }

    size = z + sizeof msg.msgtyp;   // Return size
    return 1;                       // Successful
}

// End msqrecv.cc
