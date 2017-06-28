#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

extern int scandir(const char *dirname, struct dirent ***namelist,
    int (*select)(struct dirent *),
    int (*compar)(const void *, const void *));

extern int alphasort(const void *d1, const void *d2);

/*
 * Select only those directory entries that start with
 * 'h' to demonstrate the selection ability :
 */
static int
my_select(struct dirent *dp) {

    if ( dp->d_name[0] != 'h' )
        return 0;                       /* Don't include this */
    return 1;                           /* else include this one */
}

/*
 * Sort entries in reverse order for demonstration
 * purposes :
 */
static int
my_compar(const void *d1,const void *d2) {
    struct dirent *dir1 = *(struct dirent **)d1;
    struct dirent *dir2 = *(struct dirent **)d2;

    /*
     * Reverse the comparison by reversing
     * dir2 with dir1 in the strcmp(3) call:
     */
    return strcmp(dir2->d_name,dir1->d_name);
}

/*
 * A good test is the directory /etc :
 */
int
main(int argc,char **argv) {
    int x;                              /* Work index */
    int n;                              /* namelist[n] */
    struct dirent **namelist;           /* List of names */

    if ( argc < 2 ) {
        fputs("A pathname argument is required.\n"
            "Try /etc for the directory.\n",stderr);
        return 1;
    }
    
    /*
     * Scan the directory given :
     */
    n = scandir(argv[1],&namelist,my_select,my_compar);

    /*
     * Report the directory entries :
     */
    printf("%d entries for %s:\n",n,argv[1]);
    for ( x=0; x<n; ++x )
        printf("%3d: %s\n",x,namelist[x]->d_name);

    if ( n > 0 ) {
        for ( x=0; x<n; ++x )
            free(namelist[x]);          /* Release entry */
        free(namelist);                 /* Release the array */
    }
    return 0;
}
