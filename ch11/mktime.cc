// mktime.cc

#include "dtime.h"

////////////////////////////////////////////////////////////
// This method assumes that the struct tm members of this
// class already contain valid values (tm_wday and tm_yday
// are ignored in this case):
////////////////////////////////////////////////////////////

time_t
DTime::mktime() {
    return dt = ::mktime(this);
}

// End mktime.cc
