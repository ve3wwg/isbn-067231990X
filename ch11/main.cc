// main.cc

#include "dtime.h"

int
main(int argc,char **argv) {
    DTime obj;

    (void) argc;
    (void) argv;

    // Set and display epoch time in the local time zone :
    obj.putTime(0);         // Establish epoch time
    cout << "Local UNIX Epoch time is '" << obj << "'\n\n";

    // Get and display the current time and date :
    obj.getTime();          // Get current date/time
    cout << "Current time is '" << obj << "'\n\n";

    // Compute a date 30 days from today :
    obj += 30 * 24 * 60 * 60;
    cout << "30 days from now is '" << obj << "'\n";

    // Get UTC values :
    obj.gmtime();           // Set struct tm values from time_t
    cout << "That date is " << obj.tm_mon + 1 << "/" << obj.tm_mday
        << "/" << obj.tm_year + 1900 << " "
        << obj.tm_hour << ":" << obj.tm_min << ":" << obj.tm_sec
        << " UTC\n\n";

    // Reset to local time, and set to 1st of the month :
    obj.getTime();          // Get current time
    obj.localtime();        // In local time components
    obj.tm_mday = 1;        // Set to 1st of the month
    obj.tm_hour = obj.tm_min = obj.tm_sec = 0;
    obj.mktime();           // Now set the time_t value
    cout << "The 1st is '" << obj << "' in this month\n";

    cout << "which is the same as "
        << obj.strftime("%A %B %d, %Y at %I:%M %p") << "\n";

    return 0;
}
