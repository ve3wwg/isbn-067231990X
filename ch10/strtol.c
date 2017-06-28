/* strtol.c */

#include <stdio.h>
#include <stdlib.h>

int
main(int argc,char *argv[]) {
    long lval;
    char *ep;
    static char snum[] = " -2567,45,39";

    lval = strtol(snum,&ep,10);

    printf("lval = %ld, ep = '%s'\n",lval,ep?ep:"<NULL>");

    return 0;
}
