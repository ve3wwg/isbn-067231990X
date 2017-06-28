// msqveri.cc :

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// (private) Msq::_verify :
//
//  Checks to see that the object is in a ready or
//  not ready state. If the state is not correct
//  the error EINVAL is thrown.
////////////////////////////////////////////////////////////

void
Msq::_verify(state s) {
    if ( s == ready && msqid < 0 )
        throw error = EINVAL;   // Object is not open
    if ( s != ready && msqid >= 0 )
        throw error = EINVAL;   // Object is open!
}

////////////////////////////////////////////////////////////
// Msq::dispose :
//
//  Disposes of the current message queue reference, if
//  any. The object is re-initialized to the not-ready
//  state.
////////////////////////////////////////////////////////////

Msq &
Msq::dispose() {

    key = IPC_PRIVATE;
    msqid = -1;
    return *this;
}

////////////////////////////////////////////////////////////
// Msq::Msq :
//
//  Constructor. This constructor calls upon the
//  method Msq::dispose() to initialize the object.
////////////////////////////////////////////////////////////

Msq::Msq() {
    Msq::dispose();     // Initialize this object
}

// End msqveri.cc
