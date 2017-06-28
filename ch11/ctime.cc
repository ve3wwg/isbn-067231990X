// ctime.cc

#include "dtime.h"

////////////////////////////////////////////////////////////
// Returns the ctime(3) string for the current time_t
// value that is stored in this->dt. This routine assumes
// that this->getTime() has been previously called:
////////////////////////////////////////////////////////////

char *
DTime::ctime() {
    char *cp;

    ::ctime_r(&dt,buf);     // Put ctime(3) string into buf[]
    if ( (cp = strchr(buf,'\n')) != NULL )
        *cp = 0;            // Eliminate pesky newline character
    return buf;             // Return ptr to buffer
}

// End ctime.cc
