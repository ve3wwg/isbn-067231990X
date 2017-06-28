#include <string.h>

char *
Basename(char *pathname) {
    char *cp;                    /* Work Pointer */

    if ( (cp = strrchr(pathname,'/')) )
        return cp + 1;           /* Return basename pointer */
    return pathname;             /* No directory component */
}
