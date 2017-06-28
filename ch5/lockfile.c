/* lockfile.c */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

/*
 * Lock by creating a lock file :
 */
static void
Lock(void) {
    int fd = -1;                /* Lock file descriptor */

    do  {
        fd = open("file.lck",O_WRONLY|O_CREAT|O_EXCL,0666);
        if ( fd == -1 ) {
            if ( errno == EEXIST ) {
                sleep(1);       /* Nap for a bit.. */
            } else {
                fprintf(stderr,"%s: Creating lock file.lck\n",
                    strerror(errno));
                abort();        /* Failed */
            }
        }
    } while ( fd == -1 );

    close(fd);                  /* No longer need file open */
}

/*
 * Unlock by releasing the lock file :
 */
static void
Unlock(void) {

    unlink("file.lck");         /* Release the lock file */
}

int
main(int argc,char **argv) {
    FILE *f = NULL;
    int i;
    int ch;
    int lck = 1;

    /*
     * If command line argument 1 is nolock or NOLOCK,
     * this program runs without using the Lock() and
     * Unlock() functions :
     */
    if ( argc >= 2 && !strcasecmp(argv[1],"NOLOCK") )
        lck = 0;                        /* No locking */

    printf("Process ID %ld started with %s\n",
        (long)getpid(),
        lck ? "locking" : "no locking");

    /*
     * Now create some rows of data in file.dat :
     */
    for ( i=0; i<1000; ++i ) {
        if ( lck )                      /* Using locks? */
            Lock();                     /* Yes, get lock */

        /*
         * Here we just update file.dat with new records. If
         * no locking is used while multiple processes do this,
         * some records will usually be lost. However, when
         * locking is used, no records are lost.
         *
         * Here we just open the file if it exists, otherwise
         * the file is opened for write.
         */
        f = fopen("file.dat","r+");     /* Open existing file */

        if ( !f && errno == ENOENT )
            f = fopen("file.dat","w");  /* Create file */

        if ( !f ) {
            fprintf(stderr,"%s: opening file.dat for r/w\n",
                strerror(errno));
            if ( lck )
                Unlock();               /* Unlock */
            return 1;                   /* Failed */
        }

        /*
         * Seek to the end of the file, and add a record :
         */
        fseek(f,0,SEEK_END);            /* Seek to end of file */

        fprintf(f,"%05ld i=%06d ",(long)getpid(),i);
        for ( ch=' '; ch<='z'; ++ch )
            fputc(ch,f);      /* A bunch of data to waste time */
        fputc('\n',f);

        fclose(f);

        if ( lck )                      /* Using locks? */
            Unlock();                   /* Yes, unlock */
    }

    /*
     * Announce our completion :
     */
    printf("Process ID %ld completed.\n",(long)getpid());
    return 0;
}
