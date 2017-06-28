/* mkstemp.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern int mkstemp(char *template);

int
main(int argc,char *argv[]) {
    char tf_path[64];       /* Temp. File Pathname */
    int tfd = -1;           /* File Descriptor */
    FILE *tmpf = 0;         /* Opened temp FILE */

    /*
     * Initialize the temp. file template :
     */
    strcpy(tf_path,"/var/tmp/tmp.XXXXXX");

    /*
     * Generate temp file pathname, create and open
     * the temporary file on file unit tfd :
     */
    if ( (tfd = mkstemp(tf_path)) < 0 ) {
        fprintf(stderr,"%s: generating a temp file name.\n",
            strerror(errno));
        abort();
    }

    printf("Using temp file: %s\n",tf_path);

    /*
     * Use standard I/O on temp. file :
     */
    tmpf = fdopen(tfd,"w+");
    fprintf(tmpf,"Written by PID=%ld\n",(long)getpid());
    fclose(tmpf);

    unlink(tf_path);    /* Release the temp. file */

    return 0;
}
