/* radix.c */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int
main(int argc,char *argv[]) {
    int i;              /* Iterator variable */
    char *ep;           /* End scan pointer */
    long base;          /* Conversion base */
    long lval;          /* Converted long value */

    /*
     * Test for arguments :
     */
    if ( argc < 2 ) {
        printf("Usage: %s base 'string' [base 'string]...\n",argv[0]);
        return 1;
    }

    /*
     * Process arguments :
     */
    for ( i=1; i<argc; ++i ) {
        /*
         * Get conversion base :
         */
        base = strtol(argv[i],&ep,10);
        if ( *ep != 0 ) {
            printf("Base error in '%s' near '%s'\n",argv[i],ep);
            return 1;
        } else if ( base > 36 || base < 0 ) {
            printf("Invalid base: %ld\n",base);
            return 1;
        }
        /*
         * Get conversion string :
         */
        if ( ++i >= argc ) {
            printf("Missing conversion string! Arg # %d\n",i);
            return 1;
        }

        errno = 0;      /* Clear prior errors, if any */

        lval = strtol(argv[i],&ep,(int)base);

        printf("strtol('%s',&ep,%ld) => %ld; ep='%s', errno=%d\n",
            argv[i], base, lval, ep, errno);
    }

    return 0;
}
