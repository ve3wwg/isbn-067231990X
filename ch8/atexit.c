/* atexit.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

extern char *tempnam(const char *tmpdir,const char *prefix);

static char *tf_path = NULL;    /* Temp. File Pathname */

/*
 * Cleanup function :
 */
static void
mr_clean(void) {

    puts("mr_clean() started:");

    /*
     * Here we assume, that if tf_path is not NULL, that
     * the main program has not released the temporary
     * file on its own.
     */
    if ( tf_path != NULL ) {
        printf("unlinking temp. file %s\n",tf_path);

        /*
         * Unlink the temporary file, and release the
         * pathname string :
         */
        if ( unlink(tf_path) == -1 )
            fprintf(stderr,"%s: unlink(2)\n",strerror(errno));
        free(tf_path);          /* Free the pathname string */
        tf_path = NULL;         /* Indicate that this is released */
    }

    puts("mr_clean() ended.");
}

/*
 * Main program :
 */
int
main(int argc,char *argv[]) {
    FILE *tmpf = 0;             /* Temp. File stream */

    atexit(mr_clean);           /* Register our cleanup func */

    /*
     * Create a temp. file pathname :
     */
    if ( !(tf_path = tempnam("/tmp","tmp-")) ) {
        fprintf(stderr,"%s: creating temp file.\n",strerror(errno));
        abort();
    }
    printf("Temp. file is %s\n",tf_path);

    /*
     * Create, open and write to the temp. file :
     */
    if ( !(tmpf = fopen(tf_path,"w+")) ) {
        fprintf(stderr,"%s: opening %s\n",strerror(errno),tf_path);
        abort();
    }
    fprintf(tmpf,"PID %ld was here.\n",(long)getpid());

    /*
     * Normal program exit, without unlinking the temp file:
     */
    fclose(tmpf);               /* Notice no unlink(2) here.. */
    return 0;                   /* Normal program exit */
}
