/* sscanf.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc,char *argv[]) {
    int x;
    char *datestr;      /* Date string to parse */
    int nf;             /* Number of fields converted */
    int n;              /* # of characters scanned */
    int mm, dd, yyyy;   /* Month, day and year */

    static char *sdate[] = {
        "   1 /  2  /  2000  ",
        " 03 - 9-2001,etc."
    };

    for ( x=0; x<2; ++x ) {
        datestr = sdate[x];     /* Parse this date */
        printf("Extracting from '%s'\n",datestr);

        nf = sscanf(datestr,"%d %*[/-]%d %*[/-]%d%n",&mm,&dd,&yyyy,&n);

        printf("%02d/%02d/%04d nf=%d, n=%d\n",mm,dd,yyyy,nf,n);

        if ( nf >= 3 )
            printf("Remainder = '%s'\n",&datestr[n]);
    }

    return 0;
}
