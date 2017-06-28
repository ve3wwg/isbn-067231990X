/* select.c */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

static void
quit(int rc,const char *fmt,...) {
    va_list ap;

    if ( errno != 0 )   /* Report errno */
        fprintf(stderr,"%s: ",strerror(errno));

    va_start(ap,fmt);   /* Format error message */
    vfprintf(stderr,fmt,ap);
    va_end(ap);
    fputc('\n',stderr);

    exit(rc);           /* Exit with return code */
}

int
main(int argc,char **argv) {
    int z;              /* General status code */
    int f1;             /* Open fifo 1 */
    int f2;             /* Open fifo 2 */
    fd_set rxset;       /* Read fd set */
    int nfds;           /* Number of file descriptors */
    struct timeval tv;  /* Timeout */
    char buf[200+1];    /* I/O Buffer */
    FILE *p1, *p2;      /* Pipes from popen(3) */

    /*
     * Pipes :
     */
    if ( !(p1 = popen("ls -l|tr '[a-z]' '[A-Z]'","r")) )
        quit(1,"popen(3) failed for p1");

    if ( !(p2 = popen("ls -l|tr '[A-Z]' '[a-z]' && sleep 8","r")) )
        quit(1,"popen(3) failed for p2");

    /*
     * Obtain the underlying file descriptors :
     */
    f1 = fileno(p1);
    f2 = fileno(p2);
    printf("BEGUN: f1=%d, f2=%d\n",f1,f2);

    /*
     * Enter a select loop :
     */
    do  {
        FD_ZERO(&rxset);        /* Clear set */
        if ( f1 >= 0 )
            FD_SET(f1,&rxset);  /* Check f1 */
        if ( f2 >= 0 )
            FD_SET(f2,&rxset);  /* Check f2 */

        nfds = (f1 > f2 ? f1 : f2) + 1;
        tv.tv_sec = 3;          /* 3 seconds */
        tv.tv_usec = 500000;    /* + 0.5 seconds */

        do  {
            z = select(nfds,&rxset,0,0,&tv);
        } while ( z == -1 && errno == EINTR );

        if ( z == -1 )          /* Error? */
            quit(13,"select(2)");

        if ( z == 0 ) {
            printf("TIMEOUT: f1=%d, f2=%d\n",f1,f2);
            continue;
        }

        /*
         * Control is here if f1 or f2 has data
         * available to be read.
         */
        if ( f1 >= 0 && FD_ISSET(f1,&rxset) ) {
            z = read(f1,buf,sizeof buf-1);
            if ( z == -1 )
                quit(6,"read(2) of f1.");
            if ( z > 0 ) {
                buf[z] = 0;
                printf("*** read %d bytes <<<%s>>> from f1;\n",z,buf);
            } else {
                puts("read EOF from f1;");
                pclose(p1);
                f1 = -1;
            }
        }

        if ( f2 >= 0 && FD_ISSET(f2,&rxset) ) {
            z = read(f2,buf,sizeof buf-1);
            if ( z == -1 )
                quit(6,"read(2) of f2.");
            if ( z > 0 ) {
                buf[z] = 0;
                printf("*** read %d bytes <<<%s>>> from f2;\n",z,buf);
            } else {
                puts("read EOF from f2;");
                pclose(p2);
                f2 = -1;
            }
        }

    } while ( f1 >= 0 || f2 >= 0 );

    puts("End select.");

    return 0;
}    
