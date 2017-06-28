/* madvise.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define MAX_MSGS    12              /* Limit of univ_errlist[] */

const char *univ_errlist[MAX_MSGS]; /* Universal sys_errlist[] */
const char *univ_maclist[MAX_MSGS]; /* A list of errno macro names */

static void *msgs = 0;              /* Pointer to the mapping */
static size_t msgs_len = 0;         /* Size of the mapping */

/*
 * Parse error messages from the memory mapped file, that
 * begins at address msgs for msgs_len bytes :
 */
static void
parse_messages() {
    char *mp = (char *)msgs;        /* Mapped messages address */
    char *macro, *error, *msg;
    int e;

    mp[msgs_len] = 0;               /* Store a null byte at the end */

    for ( ;; mp = NULL ) {

        macro = strtok(mp," ");     /* Extract macro name */
        if ( !macro )
            break;

        error = strtok(NULL," ");   /* Extract error # */
        if ( !error )
            break;
        if ( (e = atoi(error)) < 0 || e >= MAX_MSGS )
            break;                  /* Bad errno value */

        msg = strtok(NULL,"\n");    /* Extract message */
        if ( !msg )
            break;

        univ_errlist[e] = msg;      /* Store message */
        univ_maclist[e] = macro;    /* Macro name */
    }
}

/*
 * Map the messages file to memory, and establish
 * pointers to them by calling parse_messages() :
 */
static void
load_messages() {
    int x;                              /* Iterator */
    char *lang = getenv("MSG_LANG");    /* Get language */
    char path[256];                     /* File name */
    struct stat sbuf;                   /* stat(2) info */
    int fd = -1;                        /* Open file descriptor */

    /*
     * Load default messages :
     */
    for ( x=0; x<MAX_MSGS; ++x ) {
        univ_errlist[x] = sys_errlist[x];
        univ_maclist[x] = "?";
    }

    /*
     * Get message file's size :
     */
    sprintf(path,"./errors.%s",lang ? lang : "english");

    if ( stat(path,&sbuf) != 0 )
        return;     /* Cannot stat(2) file, so use default msgs */
    msgs_len = sbuf.st_size;

    /*
     * Open the message file for reading :
     */
    if ( (fd = open(path,O_RDONLY)) == -1 )
        return;     /* Cannot open(2) file, so use default msgs */

    /*
     * Map the language file to memory :
     */
    msgs = mmap(NULL,msgs_len+1,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);

    if ( msgs == (void *) MAP_FAILED ) {
        fprintf(stderr,"%s: mmap('%s')\n",strerror(errno),path);
        close(fd);
        return;     /* Failed, use default */
    }
    
    close(fd);      /* no longer require file to be open */

    /*
     * Advise kernel of sequential behavior :
     */
    if ( madvise(msgs,msgs_len+1,MADV_SEQUENTIAL) )
        fprintf(stderr,"%s: madvise(MADV_SEQUENTIAL)\n",strerror(errno));

    /*
     * Now parse the messages :
     */
    parse_messages();

    /*
     * Make the message text read only now :
     */
    if ( mprotect(msgs,msgs_len+1,PROT_READ) )
        fprintf(stderr,"%s: mprotect(PROT_READ)\n",strerror(errno));

    /*
     * Advise kernel of random behavior :
     */
    if ( madvise(msgs,msgs_len+1,MADV_RANDOM) )
        fprintf(stderr,"%s: madvise(MADV_SEQUENTIAL)\n",strerror(errno));
}

/*
 * Main program :
 */
int
main(int argc,char **argv) {
    int x;

    /*
     * Memory map the language file :
     */
    load_messages();
    
    /*
     * Report messages :
     */
    for ( x=1; x<MAX_MSGS; ++x )
        printf("errno=%d (%s) : %s\n",
            x,univ_maclist[x],univ_errlist[x]);

    return 0;
}
