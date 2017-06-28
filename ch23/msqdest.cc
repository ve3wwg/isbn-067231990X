// msqdest.cc

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::destroy :
//
//  Destroys the message queue. The object must be in a
//  ready state. The object is placed into a not-ready
//  state upon successful completion.
////////////////////////////////////////////////////////////

Msq &
Msq::destroy() {

    _verify(ready);     // Object must be open

    if ( msgctl(msqid,IPC_RMID,0) == -1 )
        throw error = errno;

    Msq::dispose();     // Re-initialize this object
    return *this;       // Return in not-ready state
}

// End msqdest.cc
