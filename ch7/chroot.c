/* readdir.c */

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

extern int chroot(const char *dirname);

static int
ls(const char *pathname) {
    DIR dirp = 0;               /* Open directory */
    struct dirent *dp;          /* Directory entry pointer */
    int count = 0;              /* Count of files */

    printf("DIRECTORY LISTING OF %s :\n",pathname);

    dirp = opendir(pathname);   /* Open directory */
    if ( !dirp ) {              /* errors? */
        perror("opendir(3)");
        return -1;
    }

    errno = 0;                  /* Clear errno for readdir(3) */

    while ( (dp = readdir(dirp)) != NULL ) {
        printf("%s\n",dp->d_name);
        ++count;
        errno = 0;
    }

    if ( errno != 0 ) {         /* EOF or error? */
        perror("readdir(3)");   /* Error occurred in readdir(3) */
        return -1;
    }

    if ( closedir(dirp) == -1 ) /* Close the directory */
        perror("closedir(3)");  /* Close error- report it */

    printf("%6d entries\n\n",count);

    return 0;
}

int
main(int argc,char **argv) {
    int z;
    
    z = chroot("/tmp");
    if ( z == -1 ) {
        perror("chroot(2)");
        return 1;
    }

    ls(".");
    ls("/");

    return 0;
}
