/* readdir.c */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

int
main(int argc,char **argv) {
    DIR dirp = 0;               /* Open directory */
    struct dirent *dp;          /* Directory entry pointer */

    if ( argc < 2 ) {
        fputs("A pathname argument is required.\n",stderr);
        return 1;
    }

    dirp = opendir(argv[1]);    /* Open directory */
    if ( !dirp ) {              /* errors? */
        perror("opendir(3)");
        return 2;
    }

    errno = 0;                  /* Clear errno for readdir(3) */

    while ( (dp = readdir(dirp)) != NULL ) {
        printf("%s\n",dp->d_name);
        errno = 0;
    }

    if ( errno != 0 )           /* EOF or error? */
        perror("readdir(3)");   /* Error occurred in readdir(3) */

    if ( closedir(dirp) == -1 ) /* Close the directory */
        perror("closedir(3)");  /* Close error- report it */

    return 0;
}
