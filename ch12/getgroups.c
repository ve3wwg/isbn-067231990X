/* getgroups.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>
#include <errno.h>

int
main(int argc,char **argv,char **envp) {
    int x;                                  /* Index */
    int n;                                  /* groups returned */
    struct group *grp;                      /* /etc/group entry */
    int setlen = sysconf(_SC_NGROUPS_MAX);  /* Max # groups */
    gid_t *gidset = 0;                      /* sup. grp array */

    printf("setlen = %d\n",setlen);         /* Print max # groups */
    if ( setlen < 1 )
        exit(1);                            /* Quit if we have none */
    
    /*
     * Allocate the set to maximum size :
     */
    gidset = (gid_t *) malloc(setlen * sizeof *gidset);

    /*
     * Obtain the list of supplementary groups :
     */
    n = getgroups(setlen,gidset);

    /*
     * Display the supplementary groups found :
     */
    for ( x=0; x<n; ++x ) {
        grp = getgrgid(gidset[x]);
        printf("Supplemental group: %5d  %s\n",
            gidset[x],
            grp ? grp->gr_name : "?");
    }

    return 0;
}
