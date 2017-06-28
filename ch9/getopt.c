/* getopt.c */

#include <stdio.h>
#include <unistd.h>

int
main(int argc,char **argv) {
    int rc;
    int optch;
    static char optstring[] = "cvf:";

    while ( (optch = getopt(argc,argv,optstring)) != -1 )
        switch ( optch ) {
        case 'c' :
            puts("-c processed.");
            break;
        case 'v' :
            puts("-v processed.");
            break;
        case 'f' :
            printf("-f '%s' processed.\n",optarg);
            break;
        default :   /* '?' */
            rc = 1; /* Usage error has occurred */
        }

    for ( ; optind < argc; ++optind )
        printf("argv[%d] = '%s'\n",optind,argv[optind]);

    return rc;
}
