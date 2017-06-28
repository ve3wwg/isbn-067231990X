/* tmpnam.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int
main(int argc,char *argv[]) {
    char *tmp_pathname;     /* Temp. File Pathname */
    FILE *tmpf = 0;         /* Opened temp. file */
    char cmd[256];

    if ( !(tmp_pathname = tmpnam(NULL)) ) {
        fprintf(stderr,"%s: tmpnam(3)\n",strerror(errno));
        abort();
    }

    printf("Using temp file: %s\n",tmp_pathname);

    if ( !(tmpf = fopen(tmp_pathname,"w")) ) {
        fprintf(stderr,"%s: creating temp %s\n",
            strerror(errno),tmp_pathname);
        abort();
    }
    
    sprintf(cmd,"ls -l %s",tmp_pathname);
    system(cmd);

    fclose(tmpf);           /* Close the temp file */
    unlink(tmp_pathname);   /* Release the temp file */

    return 0;
}
