/* nblockio.c */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int
main(int argc,char **argv) {
    int z;          /* # of bytes returned */
    int fd;         /* File descriptor */
    char buf[256];  /* I/O buffer */

    fd = open("./fifo",O_RDWR|O_NONBLOCK);
    if ( fd == -1 ) {
        perror("open(2)");
        exit(13);
    }

    while ( (z = read(fd,buf,sizeof buf)) == -1 && errno == EAGAIN )
        ;

    if ( z >= 0 ) {
        buf[z] = 0;

        printf("GOT INPUT! '%s'\n",buf);
    } else
        perror("read(2)");

    return 0;
}
