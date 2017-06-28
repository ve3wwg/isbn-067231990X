/* sparse.c */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>

int
main(int argc,char **argv) {
    int z;                              /* Return status code */
    off_t o;                            /* Offset */
    int fd;                             /* Read file descriptor */

    /*
     * Create/truncate sparse.dat
     */
    fd = open("sparse.dat",O_CREAT|O_WRONLY|O_TRUNC,0640);
    if ( fd == -1 ) {
        fprintf(stderr,"%s: opening sparse.dat for write\n",
            strerror(errno));
        return 1;                       /* Failed */
    }

    /*
     * Seek to almost the 1GB mark :
     */
    o = lseek(fd,1023*1024*1024,SEEK_SET); /* Seek to ~1GB */
    if ( o == (off_t)(-1) ) {
        fprintf(stderr,"%s: lseek(2)\n",strerror(errno));
        return 2;
    }

    /*
     * Write a little message :
     */
    z = write(fd,"END-OF-SPARSE-FILE",18);
    if ( z == -1 ) {
        fprintf(stderr,"%s: write(2)\n",strerror(errno));
        return 2;
    }

    close(fd);                          /* Close the file */

    return 0;
}
