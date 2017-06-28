// dtime.cc

#include <iostream.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

extern "C" {
extern char *ctime_r(const time_t *clock, char *buf);
extern struct tm *localtime_r(const time_t *clock, struct tm *result);
extern struct tm *gmtime_r(const time_t *clock, struct tm *result);
extern char *asctime_r(const struct tm *tm, char *buf);
}

////////////////////////////////////////////////////////////
// Experimental DTime Class :
////////////////////////////////////////////////////////////

class DTime : public tm {
private:
    time_t      dt;         // Date/time in epoch time
    char        buf[128];   // ctime(3)/strftime(3) buffer
public:
    DTime();
    DTime &operator+=(long secs); // Add time
    DTime &operator-=(long secs); // Subtract time
    inline time_t time() { return dt; }
    time_t getTime();       // time(3)
    time_t putTime(time_t dt); // Put a time value into this->dt
    char *ctime();          // ctime(3)
    struct tm *localtime(); // localtime(3)
    struct tm *gmtime();    // gmtime(3)
    char *asctime();        // asctime(3)
    time_t mktime();        // mktime(3)
    char *strftime(const char *format); // strftime(3)
};

extern ostream &operator<<(ostream &ostr,DTime &obj);

// End dtime.h
