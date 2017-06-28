// localtime.cc

#include "dtime.h"

////////////////////////////////////////////////////////////
// Return the local time components, based upon the
// current value of this->dt; assumes that a prior
// call to getTime() has been made:
////////////////////////////////////////////////////////////

struct tm *
DTime::localtime() {
    ::localtime_r(&dt,this);
    return this;
}

////////////////////////////////////////////////////////////
// Return the UTC (GMT) time components, based upon the
// current value of this->dt; assumes that a prior
// call to getTime() has been made:
////////////////////////////////////////////////////////////

struct tm *
DTime::gmtime() {
    ::gmtime_r(&dt,this);
    return this;
}

// End localtime.cc
