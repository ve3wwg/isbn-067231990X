// getuid.cc

#include <errno.h>
#include "passwd.h"

////////////////////////////////////////////////////////////
// LOOKUP UID VALUE:
//      Returns ptr to this->pw_name
//      Throws errno if call fails
////////////////////////////////////////////////////////////

char *
Passwd::getuid(uid_t uid) {
    passwd *p = 0;

    if ( state == defined )
        _dispose();             // Dispose of content

    e = errno = 0;              // Clear errno
    p = ::getpwuid(uid);        // Look up uid

    if ( !p ) {
        if ( !errno )
            e = ENOENT;         // Use ENOENT for "not found"
        else
            e = errno;          // Capture errno
        throw e;                // throw the error
    }

    _import(p);                 // Copy to this object
    return this->pw_name;       // Return login name
}

////////////////////////////////////////////////////////////
// LOOKUP LOGIN NAME :
//      Returns uid_t value
//      Throws errno if call fails
////////////////////////////////////////////////////////////

int
Passwd::getnam(const char *name) {
    passwd *p = 0;

    if ( state == defined )
        _dispose();             // Dispose of content

    e = errno = 0;              // Clear errno
    p = ::getpwnam(name);       // Look up uid

    if ( !p ) {
        if ( !errno )
            e = ENOENT;         // Use ENOENT for "not found"
        else
            e = errno;          // Else capture errno
        throw e;                // Throw the error
    }

    _import(p);                 // Copy to this object
    return p->pw_uid;           // Return uid #
}

// End getuid.cc
