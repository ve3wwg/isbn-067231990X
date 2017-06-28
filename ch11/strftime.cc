// strftime.cc

#include "dtime.h"

////////////////////////////////////////////////////////////
// Call strftime(3) to format a string, based upon the
// current struct tm members. This method assumes that the
// struct tm members contain valid values.
////////////////////////////////////////////////////////////

char *
DTime::strftime(const char *format) {
    size_t n = ::strftime(buf,sizeof buf-1,format,this);
    buf[n] = 0;             // Enforce a null byte
    return buf;             // Return formatted string
}

////////////////////////////////////////////////////////////
// Output operator for the DTime object :
////////////////////////////////////////////////////////////

ostream &
operator<<(ostream &ostr,DTime &obj) {

    if ( obj.time() == (time_t)(-1) )
        ostr << "[No current time]";
    else
        ostr << obj.ctime();
    return ostr;
}

// End strftime.cc
