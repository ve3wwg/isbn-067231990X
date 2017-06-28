/* unixio.c */

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
    int n;                              /* # of bytes written */
    int fd;                             /* Read file descriptor */
    char buf[128];                      /* I/O Buffer */
    char *pathname = "/etc/motd";       /* Default file to open */

    if ( argc > 1 )
        pathname = argv[1];             /* Choose a different file */

    fd = open(pathname,O_RDONLY);       /* Open /etc/motd file */

    if ( fd == -1 ) {
        fprintf(stderr,"%s: opening %s for read\n",
            strerror(errno),pathname);
        return 1;                       /* Failed */
    }

    for (;;) {
        z = read(fd,buf,sizeof buf);    /* Fill buf with read data */
        if ( !z )
            break;                      /* End of file */
        if ( z == -1 ) {
            fprintf(stderr,"%s: reading file %s\n",
                strerror(errno),pathname);
            return 2;                   /* Failed */
        }

        n = write(1,buf,z);             /* Write out buffer contents */
        if ( n == -1 ) {
            fprintf(stderr,"%s: writing to stdout\n",strerror(errno));
            return 3;                   /* Failed */
        }
    }

    close(fd);                          /* Close the file */

    return 0;
}
