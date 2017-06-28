/* regexpr.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

/*
 * Provide usage instructions :
 */
static void
usage(void) {

    puts("Usage:\tregexpr [options] pattern <file");
    puts("Options:");
    puts("\t-e\tREG_EXTENDED");
    puts("\t-b\tREG_BASIC");
    puts("\t-n\tREG_NOSPEC");
    puts("\t-i\tREG_ICASE");
    puts("\t-s\tREG_NOSUB");
}

/*
 * Perform a substring operation :
 */
static char *
substr(const char *str,unsigned start,unsigned end) {
    unsigned n = end - start;
    static char stbuf[256];     /* Local static buffer */

    strncpy(stbuf,str+start,n); /* Copy substring */
    stbuf[n] = 0;               /* Null terminate */
    return stbuf;               /* Return static buffer */
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    int z;                      /* General status code */
    int x;                      /* Loop iterator */
    int lno = 0;                /* Line number */
    int cmdopt_h = 0;           /* -h ; usage option */
    int cflags = 0;             /* Compile flags */
    regex_t reg;                /* Compiled regular expression */
    char *pattern;              /* Regular expression */
    const size_t nmatch = 10;   /* The size of array pm[] */
    regmatch_t pm[10];          /* Pattern matches 0-9 */
    char ebuf[128];             /* Error message buffer */
    char lbuf[256];             /* Line buffer */
    const char cmdopts[] = "hebnis";

    while ( (z = getopt(argc,argv,cmdopts)) != -1 )
        switch ( z ) {
        case 'b' :
            cflags |= REG_BASIC;
            break;
        case 'e' :
            cflags |= REG_EXTENDED;
            break;
        case 'n' :
            cflags |= REG_NOSPEC;
            break;
        case 'i' :
            cflags |= REG_ICASE;
            break;
        case 's' :
            cflags |= REG_NOSUB;
            break;
        case 'h' :
        default  :
            cmdopt_h = 1;
        }

    if ( optind + 1 != argc || cmdopt_h ) {
        usage();
        return 1;
    }

    /*
     * Compile the regular expression :
     */
    pattern = argv[optind];

    z = regcomp(&reg,pattern,cflags);

    if ( z != 0 ) {
        regerror(z,&reg,ebuf,sizeof ebuf);
        fprintf(stderr,"%s: pattern '%s'\n",ebuf,pattern);
        return 1;
    }

    /*
     * Report the number of subexpressions :
     */
    if ( !(cflags & REG_NOSUB) )
        printf("There were %d subexpressions.\n",reg.re_nsub);

    /*
     * Now process each line for matches :
     */
    while ( fgets(lbuf,sizeof lbuf,stdin) ) {
        ++lno;                      /* Increment the line number */
        if ( (z = strlen(lbuf)) > 0 && lbuf[z-1] == '\n' )
            lbuf[z-1] = 0;          /* Eliminate newline character */

        /*
         * Now apply regular expression matching to this line :
         */
        z = regexec(&reg,lbuf,nmatch,pm,0);

        if ( z == REG_NOMATCH )
            continue;
        else if ( z != 0 ) {
            regerror(z,&reg,ebuf,sizeof ebuf);
            fprintf(stderr,"%s: regcomp('%s')\n",ebuf,lbuf);
            return 2;
        }

        for ( x=0; x<nmatch && pm[x].rm_so != -1; ++x ) {
            if ( !x )   /* Print the matching line number */
                printf("%04d: %s\n",lno,lbuf);
            printf("  $%d='%s'\n",
                x,                  /* Report substring $x */
                substr(lbuf,pm[x].rm_so,pm[x].rm_eo));
        }
    }

    regfree(&reg);                  /* Free compiled regexpr */
    return 0;
}
