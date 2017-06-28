// msqsend.cc :

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::send :
//
// ARGUMENTS :
//  msg         The message to be sent
//  size        The total size of the message
//  flags       zero or IPC_NOWAIT (optional)
//
// RETURNS:
//  0           No message sent (with IPC_NOWAIT)
//  1           Message was sent
//
//  Sends a message of size bytes to the message queue.
//  The size must include the total size of the message,
//  including the message type. The object must be in a
//  ready state.
////////////////////////////////////////////////////////////

int
Msq::send(Msg &msg,size_t size,int flags) {
    int z;
    size_t msgsz = size - sizeof msg.msgtyp;

    _verify(ready);

    do  {
        z = msgsnd(msqid,&msg,msgsz,flags);
    } while ( z == -1 && errno == EINTR );

    if ( z ) {
        if ( flags & IPC_NOWAIT && errno == EAGAIN )
            return 0;   // Not sent

        // Other fatal error:
        throw error = errno;
    }

    return 1;           // Succeeded
}

// End msqsend.cc
