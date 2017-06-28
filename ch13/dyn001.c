/* dyn001.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int
sum_ints(int n,...) {
    va_list ap;
    int x;
    int sum = 0;

    va_start(ap,n);

    for ( ; n>0; --n ) {
        x = va_arg(ap,int);
        sum += x;
    }

    va_end(ap);

    return sum;
}

/* End dyn001.c */
