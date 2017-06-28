/* tempnam.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern char *tempnam(const char *tmpdir, const char *prefix);

int
main(int argc,char *argv[]) {
    char *tf_path = NULL;       /* Temp. File Pathname */
    FILE *tmpf = 0;             /* Temp. File stream */

    if ( !(tf_path = tempnam("./my_tmp","tmp-")) ) {
        fprintf(stderr,"%s: generating a temp file name.\n",
            strerror(errno));
        abort();
    }

    printf("Temp. file name is %s\n",tf_path);

    if ( !(tmpf = fopen(tf_path,"w+")) ) {
        fprintf(stderr,"%s: opening %s for I/O\n",
            strerror(errno),tf_path);
        abort();
    }

    fprintf(tmpf,"PID %ld was here.\n",(long)getpid());
    fclose(tmpf);

    unlink(tf_path);            /* Release the temp file */
    free(tf_path);              /* Free allocated string */

    return 0;
}
