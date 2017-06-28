// msqcr.cc :

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::create :
//
// ARGUMENTS:
//  key         IPC Key of the message queue or IPC_PRIVATE
//  flags       The permission bits, and possibly IPC_EXCL
//
//  This method creates a message queue. Object must be
//  in a not-ready state.
////////////////////////////////////////////////////////////

Msq &
Msq::create(key_t key,int flags) {

    _verify(notReady);  // Object must not be open

    flags |= IPC_CREAT; // Force a create symantic

    /*
     * Attempt to create the message queue :
     */
    msqid = msgget(this->key = key,flags);
    if ( msqid == -1 )
        throw error = errno;

    return *this;
}

// End msqcr.cc
