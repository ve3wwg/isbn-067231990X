/* convrt.c */

#include "semop.h"

/*
 * Convert string to unsigned long (any radix) :
 */
int
cvt2ulong(const char *str,unsigned long *ulp) {
    char *ep;
    unsigned long ul;

    ul = strtoul(str,&ep,0);
    if ( *ep != 0 )
        return -1;      /* Failed */

    if ( ulp )
        *ulp = ul;
    return 0;           /* Success */
}

/*
 * Parse and convert up to n_sem values to array :
 */
int
cvt2array(const char *str,int array[],const char *delim) {
    char *cp;                       /* Token pointer */
    int n = 0;                      /* # of values extracted */
    int m = *delim == '=' ? 2 : n_sem; /* only 2 if using '=' */
    unsigned long ul;               /* converted ulong value */

    for ( cp=(char *)str; n<m && *cp; ++n ) {
        ul = strtoul(cp,&cp,0);     /* Convert to ulong */
        if ( *cp && !strchr(delim,*cp) )
            return -1;              /* Failed conversion */
        array[n] = (int)ul;         /* Save ulong value in array */
        if ( *cp )
            ++cp;                   /* Skip delimiter */
    }

    return n;                       /* Return # of values */
}

/*
 * -o 0=-1u,2=-3U,1=1
 *
 * Translates to:
 *
 *  Semaphore 0 does a wait of 1, with no SEM_UNDO
 *  Semaphore 2 does a wait of 3, with SEM_UNDO
 *  Semaphore 1 does a notify of 1, with current SEM_UNDO flag
 */
int
cvt2semops(const char *str,int sems[],int array[],int flags[]) {
    int x = 0;
    int semx;                       /* Semaphore index */
    char *ep = (char *)str;
    unsigned long ul;
    long lg;

    for ( x=0; *ep && x<n_sem; ++x ) {
        /*
         * Extract the semaphore # :
         */
        ul = strtoul(ep,&ep,0);
        if ( *ep != '=' )
            return -1;              /* Bad format */
        semx = sems[x] = (int) ul;  /* Semaphore # */
        ++ep;                       /* Skip '=' */

        /*
         * Extract the Semaphore operation :
         */
        lg = strtol(ep,&ep,0);
        if ( *ep != 0 && *ep != ',' && *ep != 'u' && *ep != 'U' )
            return -1;              /* Bad format */
        array[x] = (int) lg;        /* Semaphore operation */

        /*
         * Process optional trailing 'u'|'U' for flags[] :
         */
        if ( *ep == 'u' ) {
            flags[semx] &= ~SEM_UNDO;/* Remove SEM_UNDO */
            ++ep;                   /* Skip 'u' */
        } else if ( *ep == 'U' ) {
            flags[semx] |= SEM_UNDO;/* Add SEM_UNDO */
            ++ep;                   /* Skip 'U' */
        }

        /*
         * Check current delimiter :
         */
        if ( *ep != 0 ) {
            if ( *ep != ',' )
                return -1;          /* Bad format */
            ++ep;                   /* Skip delimiter */
        }
    }    

    return x;
}
