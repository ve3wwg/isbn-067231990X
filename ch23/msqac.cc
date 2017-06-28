// msqac.cc :

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::access :
//
// ARGUMENTS:
//  key         IPC Key of the message queue or IPC_PRIVATE
//
//  This method accesses a message queue. Object must be
//  in a not-ready state.
////////////////////////////////////////////////////////////

Msq &
Msq::access(key_t key) {

    _verify(notReady);  // Object must not be open

    /*
     * Attempt to create the message queue :
     */
    msqid = msgget(this->key = key,0);
    if ( msqid == -1 )
        throw error = errno;

    return *this;
}

// End msqac.cc
