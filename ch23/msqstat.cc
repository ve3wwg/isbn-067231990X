// msqstat.cc

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::stat :
//
// ARGUMENTS :
//  stbuff      The struct msqid_ds structure to populate
//              with message queue information.
//
//  This method fills the supplied buffer with status
//  information about the current queue. The object must
//  be in the ready state.
////////////////////////////////////////////////////////////

msqid_ds &
Msq::stat(msqid_ds &stbuf) {

    _verify(ready);     // Object must be open
    
    if ( msgctl(msqid,IPC_STAT,&stbuf) == -1 )
        throw error = errno;

    return stbuf;
}

// End msqstat.cc
