// msqchg.cc

#include <stdlib.h>
#include <errno.h>
#include "msq.h"

////////////////////////////////////////////////////////////
// Msq::change :
//
// ARGUMENTS :
//  stbuff      The struct msqid_ds structure containing
//              the changes to be made.
//
//  Only the values msg_perm.uid, msg_perm.gid, msg_perm.mode
//  and msg_qbytes values can be changed. The value
//  msg_qybytes can only be increased by the superuser.
//  Object must be in the ready state.
////////////////////////////////////////////////////////////

Msq &
Msq::change(msqid_ds &stbuf) {

    _verify(ready);     // Object must be open
    
    if ( msgctl(msqid,IPC_SET,&stbuf) == -1 )
        throw error = errno;

    return *this;
}

// End msqchg.cc
