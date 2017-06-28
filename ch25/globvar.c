/* globvar.c */

#include "globvar.h"

int shmid = -1;                 /* IPC ID of shared memory */
GlobVars *globvars = NULL;      /* Shared memory region */

/*
 * Usage instructions :
 */
static void
usage(void) {

    puts("globvar [-i] [-s size] [-e] [-u] [-r] [-c]"
        " var... var=value...");
    puts("Options:");
    puts("    -i          Initialize new globvar pool");
    puts("    -s size     Size of this pool, in bytes");
    puts("    -e          Dump all values (after changes)");
    puts("    -u          Unset all named variables");
    puts("    -r          Remove this pool of values");
    puts("    -c          Clear all variables");
    puts("    -h          This info.");
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    int rc = 0;                 /* Return code */
    int optch;                  /* Option character */
    int cmdopt_i = 0;           /* -i to create var pool */
    int cmdopt_c = 0;           /* -c to clear variables */
    int cmdopt_r = 0;           /* -r to remove pool */
    int cmdopt_e = 0;           /* -D to dump the variables */
    int cmdopt_u = 0;           /* -u to unset named variables */
    int cmdopt_h = 0;           /* -h usage option */
    int cmdopt_s = 4096;        /* Default for -s */
    char *cp, *ep;              /* Character pointers */
    unsigned long ul;           /* Converted ulong */
    const char cmdopts[] = "hirs:ecu";

    /*
     * Parse command line options :
     */
    while ( (optch = getopt(argc,argv,cmdopts)) != -1 )
        switch ( optch ) {
        case 'c' :              /* -c to clear variables */
            cmdopt_c = 1;
            break;

        case 'i' :              /* -i initialize a new pool */
            cmdopt_i = 1;
            break;

        case 'e' :              /* -e to dump all variables like env */
            cmdopt_e = 1;
            break;

        case 'r' :              /* -r to remove the pool */
            cmdopt_r = 1;
            break;

        case 's' :              /* -s size; affects -i */
            ul = strtoul(optarg,&ep,0);
            if ( *ep ) {
                fprintf(stderr,"Bad size: -s %s\n",optarg);
                rc = 1;
            } else
                cmdopt_s = (int) ul;
            break;

        case 'u' :              /* -u to unset all listed variables */
            cmdopt_u = 1;
            break;

        case 'h' :              /* -h to request help */
            cmdopt_h = 1;
            break;

        default  :
            rc = 1;
        }

    /*
     * Give usage display if errors or -h :
     */
    if ( cmdopt_h || rc ) {
        usage();
        if ( rc )
            return rc;
    }

    /*
     * Create/Access global variable pool :
     */
    if ( cmdopt_i ) {
        /*
         * Create a new shared memory variable pool :
         */
        create_vars(cmdopt_s);
        printf("%d\n",shmid);

    } else if ( (cp = getenv(GLOBVARENV)) != NULL ) {
        /*
         * Extract IPC key from GLOBVAR environment variable :
         */
        ul = strtoul(cp,&ep,0);
        if ( *ep ) {
            fprintf(stderr,"%s has bad IPC key\n",cp);
            return 1;
        }

        shmid = (int)ul;
        attach_vars();
    }

    /*
     * Do we have enough information to find the pool?
     */
    if ( !globvars ) {
        fprintf(stderr,"You must use -i or define"
            " environment variable %s.\n",GLOBVARENV);
        return 1;
    }

    /*
     * -c clears all variables :
     */
    if ( cmdopt_c ) {
        glob_lock();
        globvars->vars[0] = globvars->vars[1] = 0;
        glob_unlock();
    }

    /*
     * Now process variable requests :
     */
    for ( ; optind < argc; ++optind ) {
        cp = strchr(argv[optind],'=');

        glob_lock();

        if ( !cp ) {
            /*
             * Just have a variable name, so return value or unset :
             */
            if ( !cmdopt_u ) {
                if ( (cp = get_var(argv[optind])) != NULL ) {
                    puts(cp);   /* Just emit value of variable */
                } else {
                    fprintf(stderr,"Variable %s not found\n",argv[optind]);
                    rc = 1;
                }
            } else
                unset_var(argv[optind]);

        } else {
            /*
             * Change the variable's value :
             */
            *cp = 0;
            set_var(argv[optind],++cp);
        }

        glob_unlock();
    }

    /*
     * Dump all variables (for debugging) :
     */
    if ( cmdopt_e ) {
        glob_lock();
        for ( cp=&globvars->vars[0]; *cp; cp+=strlen(cp)+1 )
            puts(cp);
        glob_unlock();
    }

    /*
     * If -r option, destroy the global variable pool :
     */
    if ( cmdopt_r )
        destroy_vars();

    return rc;
}
