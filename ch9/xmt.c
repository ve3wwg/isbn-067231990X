/* xmt.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *suboptarg;
int getsubopt(char **optionp, char * const *tokens, char **valuep);

int
main(int argc,char **argv) {
    int rc = 0;         /* Return code */
    int x;              /* Arg index */
    int n;              /* Int value */
    char *valuep;       /* Ptr to subopt value */
    int optch;          /* Option character */
    static char optstring[] = "f:c:";

    /* Suboptions Table of Tokens : */
    static char *tokens[] = {
#define _SO_WEOF    0
        "weof",         /* Write n EOF marks */
#define _SO_FSF     1
        "fsf",          /* Forward space file */
#define _SO_BSF     2
        "bsf",          /* Back space file */
#define _SO_REWIND  3
        "rewind",       /* Rewind tape */   
        NULL
    };

    /*
     * Process all command line options :
     */
    while ( (optch = getopt(argc,argv,optstring)) != -1 )
        switch ( optch ) {

        case 'f' :      /* -f device */
            printf("-f '%s' (tape device).\n",optarg);
            break;

        case 'c' :      /* -c commands */
            /*
             * Process all suboptions for -c :
             */
            while ( *optarg != 0 ) 
                switch ( (x = getsubopt(&optarg,tokens,&valuep)) ) {

                case _SO_WEOF :
                    n = !valuep ? 1 : atoi(valuep);
                    printf("Write %d EOF marks (%s=%s)\n",
                        n,suboptarg,valuep);
                    break;

                case _SO_FSF :
                    n = !valuep ? 1 : atoi(valuep);
                    printf("Forward space %d file(s) (%s=%s)\n",
                        n,suboptarg,valuep);
                    break;

                case _SO_BSF :
                    n = !valuep ? 1 : atoi(valuep);
                    printf("Backspace %d file(s) (%s=%s)\n",
                        n,suboptarg,valuep);
                    break;

                case _SO_REWIND :
                    if ( valuep ) {
                        printf("Suboption %s does not take a arg\n",
                            suboptarg);
                        rc = 1;     /* Flag usage error */
                    } else
                        printf("Rewind tape (%s)\n",suboptarg);
                    break;

                case -1 :
                    printf("Illegal suboption %s%s%s\n",
                        suboptarg,
                        valuep ? "=" : "",
                        valuep ? valuep : "");
                    break;

                default :
                    abort();    /* Should never get here */                 
                }
            break;

        default :   /* '?' */
            rc = 1; /* Usage error has occurred */
        }

    /*
     * Report all arguments :
     */
    for ( ; optind < argc; ++optind )
        printf("argv[%d] = '%s'\n",optind,argv[optind]);

    return rc;
}
