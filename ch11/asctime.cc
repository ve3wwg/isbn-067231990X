// asctime.cc

#include "dtime.h"

////////////////////////////////////////////////////////////
// This function returns the asctime(3) string, for the
// present members of this class (struct tm). This method
// assumes that the present struct tm members are valid.
////////////////////////////////////////////////////////////

char *
DTime::asctime() {
    return ::asctime_r(this,buf);
}

// End asctime.cc
