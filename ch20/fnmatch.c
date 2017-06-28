/* fnmatch.c */

#include <stdio.h>
#include <unistd.h>
#include <fnmatch.h>

/*
 * Provide command usage instructions :
 */
static void
usage(void) {

    puts("Usage: fnmatch [options] <pattern> <strings>...");
    puts("\nOptions:");
    puts("\t-n\tShow non-matches");
    puts("\t-e\tFNM_NOESCAPE");
    puts("\t-p\tFNM_PATHNAME");
    puts("\t-P\tFNM_PERIOD");
    puts("\t-d\tFNM_LEADING_DIR");
    puts("\t-c\tFNM_CASEFOLD");
}    

/*
 * Report the flag bits in use as confirmation :
 */
static void
report_flags(int flags) {

    fputs("Flags:",stdout);
    if ( flags & FNM_NOESCAPE )
        fputs(" FNM_NOESCAPE",stdout);
    if ( flags & FNM_PATHNAME )
        fputs(" FNM_PATHNAME",stdout);
    if ( flags & FNM_PERIOD )
        fputs(" FNM_PERIOD",stdout);
    if ( flags & FNM_LEADING_DIR )
        fputs(" FNM_LEADING_DIR",stdout);
    if ( flags & FNM_CASEFOLD )
        fputs(" FNM_CASEFOLD",stdout);
    if ( !flags )
        puts(" NONE");
    else
        putchar('\n');
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    int x;                      /* Interator variable */
    int z;                      /* General status variable */
    int flags = 0;              /* fnmatch(3) flags argument */
    int cmdopt_n = 0;           /* When true, report non-matches */
    char *pattern;              /* Pattern string for fnmatch(3) */
    const char cmdopts[] = "epPdchn"; /* Supported command options */
    
    /*
     * Process any command options :
     */
    while ( (z = getopt(argc,argv,cmdopts)) != -1 )
        switch ( z ) {
        case 'e' :
            flags |= FNM_NOESCAPE;      /* -e */
            break;
        case 'p' :
            flags |= FNM_PATHNAME;      /* -p */
            break;
        case 'P' :
            flags |= FNM_PERIOD;        /* -P */
            break;
        case 'd' :
            flags |= FNM_LEADING_DIR;   /* -d */
            break;
        case 'c' :
            flags |= FNM_CASEFOLD;      /* -c */
            break;
        case 'n' :
            cmdopt_n = 1;               /* -n ; Show non-matches */
            break;
        case 'h' :
        default :
            usage();
            return 1;
        }

    /*
     * We must have a pattern and at least one trial string :
     */
    if ( optind + 1 >= argc ) {
        usage();
        return 1;
    }

    /*
     * Pick the pattern string and report the flags that
     * are in effect for this run :
     */
    pattern = argv[optind++];
    report_flags(flags);

    /*
     * Now try pattern against all remaining command
     * line arguments :
     */
    for ( x=optind; x<argc; ++x ) {
        z = fnmatch(pattern,argv[x],flags);
        /*
         * Report matches, or report all, if -n
         * option was used :
         */
        if ( !z || cmdopt_n )
            printf("%s: fnmatch('%s','%s',flags)\n",
                !z ? "Matched" : "No match",
                pattern,
                argv[x]);
    }

    return 0;
}
