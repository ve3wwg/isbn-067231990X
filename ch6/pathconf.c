/* pathconf.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main(int argc,char **argv) {
    int x;
    struct  {
        int     test;
        char    *desc;
    } tests[] = {
        { _PC_LINK_MAX, "The maximum file link count." },
        { _PC_MAX_CANON, "The maximum number of bytes \n"
                    "\tin terminal canonical input line." },
        { _PC_MAX_INPUT, "The minimum maximum number\n"
                "\tof bytes for which space is available\n"
                "\tin a terminal input queue." },
        { _PC_NAME_MAX, "The maximum number of bytes in\n"
                "\ta file name." },
        { _PC_PATH_MAX, "The maximum number of bytes\n"
                "\tin a pathname." },
        { _PC_PIPE_BUF, "The maximum number of bytes\n"
                "\twhich will be written atomically to a pipe." },
        { _PC_CHOWN_RESTRICTED, "Return 1 if appropriate\n"
                "\tprivileges are required for the chown(2)\n"
                "\tsystem call, otherwise 0." },
        { _PC_NO_TRUNC, "Return 1 if file names longer\n"
                "\tthan KERN_NAME_MAX are truncated." },
        { _PC_VDISABLE, "Returns the terminal character\n"
                "\tdisabling value." },
    };
    long lv;    

    for ( x=0; x<sizeof tests/sizeof tests[0]; ++x ) {
        errno = 0;                          /* Clear */
        lv = pathconf(".",tests[x].test);   /* Use dir . */
        if ( lv == -1L && errno == EINVAL )
            lv = fpathconf(0,tests[x].test);/* Use fd=0 */

        if ( lv == -1L ) {             /* Test if error */
            if ( errno )
                printf("%s: %s\n",strerror(errno),tests[x].desc);
            else
                printf("The value test[%d] is not supported.\n",x);
            continue;
        }

        printf("%ld:\t%s\n",lv,tests[x].desc);
    }

    return 0;
}
