/* glob.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <glob.h>

/*
 * Provide command usage instructions :
 */
static void
usage(void) {

    puts("Usage: glob [options] pattern...");
    puts("Options:");
    puts("\t-a\tGLOB_APPEND");
    puts("\t-c\tGLOB_NOCHECK");
    puts("\t-o n\tGLOB_DOOFFS");
    puts("\t-e\tGLOB_ERR");
    puts("\t-m\tGLOB_MARK");
    puts("\t-n\tGLOB_NOSORT");
    puts("\t-B\tGLOB_BRACE");
    puts("\t-N\tGLOB_NOMAGIC");
    puts("\t-Q\tGLOB_QUOTE");
    puts("\t-T\tGLOB_TILDE");
}    

/*
 * Report the flag bits in use as confirmation :
 */
static void
report_flags(int flags) {

    fputs("Flags:",stdout);
    if ( flags & GLOB_APPEND )
        fputs(" GLOB_APPEND",stdout);
    if ( flags & GLOB_DOOFFS )
        fputs(" GLOB_DOOFFS",stdout);
    if ( flags & GLOB_ERR )
        fputs(" GLOB_ERR",stdout);
    if ( flags & GLOB_MARK )
        fputs(" GLOB_MARK",stdout);
    if ( flags & GLOB_NOSORT )
        fputs(" GLOB_NOSORT",stdout);
    if ( flags & GLOB_NOCHECK )
        fputs(" GLOB_NOCHECK",stdout);
    if ( flags & GLOB_BRACE )
        fputs(" GLOB_BRACE",stdout);
    if ( flags & GLOB_MAGCHAR )
        fputs(" GLOB_MAGCHAR",stdout);
    if ( flags & GLOB_NOMAGIC )
        fputs(" GLOB_NOMAGIC",stdout);
    if ( flags & GLOB_QUOTE )
        fputs(" GLOB_QUOTE",stdout);
    if ( flags & GLOB_TILDE )
        fputs(" GLOB_TILDE",stdout);
    if ( !flags )
        puts(" NONE");
    else
        putchar('\n');
}

/*
 * Error callback function :
 */
static int
errfunc(const char *path,int e) {
    printf("%s: %s\n",strerror(e),path);
    return 0;
}

/*
 * Report the glob_t results :
 */
static void
report_glob(glob_t *gp) {
    int x;
    int g_offs = 0;             /* glob offset */

    if ( gp->gl_pathc < 1 ) {
        puts("There are no glob results.");
        return;
    }
    printf("There were %d matches returned:\n",gp->gl_pathc);

    if ( gp->gl_flags & GLOB_DOOFFS )
        g_offs = gp->gl_offs;   /* Allow for offset */

    for ( x=0; x < gp->gl_pathc + g_offs; ++x )
        printf("%3d: %s\n",
            x,
            gp->gl_pathv[x] ? gp->gl_pathv[x] : "<NULL>");

    report_flags(gp->gl_flags);
    putchar('\n');
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    int z;                      /* General status */
    glob_t g;                   /* The glob area */
    int flags = 0;              /* All other flags */
    int a = 0;                  /* GLOB_APPEND flag */
    int offs = 0;               /* Offset */
    const char cmdopts[] = "aco:emnBNQTh";
    
    /*
     * Process any command options :
     */
    while ( (z = getopt(argc,argv,cmdopts)) != -1 )
        switch ( z ) {
        case 'a' :
            a = GLOB_APPEND;
            break;
        case 'o' :
            flags |= GLOB_DOOFFS;
            offs = atoi(optarg);
            break;
        case 'e' :
            flags |= GLOB_ERR;
            break;
        case 'm' :
            flags |= GLOB_MARK;
            break;
        case 'n' :
            flags |= GLOB_NOSORT;
            break;
        case 'c' :
            flags |= GLOB_NOCHECK;
            break;
        case 'B' :
            flags |= GLOB_BRACE;
            break;
        case 'N' :
            flags |= GLOB_NOMAGIC;
            break;
        case 'Q' :
            flags |= GLOB_QUOTE;
            break;
        case 'T' :
            flags |= GLOB_TILDE;
            break;
        case 'h' :
        default :
            usage();
            return 1;
        }

    /*
     * We must have at least one pattern :
     */
    if ( optind >= argc ) {
        usage();
        return 1;
    }

    /*
     * Pick the pattern string and report the flags that
     * are in effect for this run :
     */
    report_flags(flags|a);

    /*
     * Now try pattern against all remaining command
     * line arguments :
     */
    for ( ; optind < argc; ++optind, flags |= a ) {
        /*
         * Invoke glob(3) to scan directories :
         */
        g.gl_offs = offs;       /* Offset, if any */
        z = glob(argv[optind],flags,errfunc,&g);
        if ( z ) {
            if ( z == GLOB_NOSPACE )
                fputs("glob(3) ran out of memory\n",stderr);
            else if ( z == GLOB_ABEND )
                fputs("glob(3): GLOB_ERR/errfunc\n",stderr);
            return 1;
        }

        /*
         * Report glob(3) findings, unless GLOB_APPEND :
         */
        if ( !a ) {             /* If not GLOB_APPEND */
            report_glob(&g);    /* Report matches */
            globfree(&g);       /* Free gl_pathv[] etc. */
        } else {
            /*
             * GLOB_APPEND requested. Just accumulate
             * glob(3) results, but here we report the
             * number of matches made with each pattern:
             */
            printf("Pattern '%s' got %d matches\n",
                argv[optind],
                g.gl_matchc);
        }
    }

    /*
     * If GLOB_APPEND used, then report everything at
     * the end :
     */
    if ( a ) {                  /* If GLOB_APPEND */
        report_glob(&g);        /* Report appended matches */
        globfree(&g);           /* Free gl_pathv[] etc. */
    }

    return 0;
}
