// SnapShot.cc

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

#include "Dir.h"
#include "InoDb.h"

static int rc = 0;              // return code
static int cmdopt_i = 0;        // -i
static int cmdopt_c = 0;        // -c
static int cmdopt_v = 0;        // -v
static int cmdopt_h = 0;        // -h

////////////////////////////////////////////////////////////
// RETURN BASENAME OF A PATHNAME :
////////////////////////////////////////////////////////////

char *
Basename(char *path) {
    char *bname = strrchr(path,'/');

    return !bname ? path : bname + 1;
}

////////////////////////////////////////////////////////////
// COMPARE CURRENT VS PRIOR STAT(2) INFO :
////////////////////////////////////////////////////////////

char *
Compare(struct stat is,struct stat was) {
    static char cmpmsg[512];    // Compare() message buffer
    static char dtbuf[64];      // Date time format buffer
    struct passwd *pw;          // /etc/password lookup
    struct group *gr;           // /etc/group lookup

    // DID THE FILE SIZE CHANGE?
    if ( is.st_size != was.st_size ) {
        sprintf(cmpmsg,"Size has changed (was %ld bytes)",
            (long)was.st_size);
        return cmpmsg;
    }

    // DID THE FILE MODIFICATION TIME CHANGE?
    if ( is.st_mtime != was.st_mtime ) {
        strftime(dtbuf,sizeof dtbuf,"%x %X",localtime(&was.st_mtime));
        dtbuf[sizeof dtbuf-1] = 0;
        sprintf(cmpmsg,"Modification time has changed (was %s)",dtbuf);
        return cmpmsg;
    }

    // DID THE FILE MODE CHANGE?
    if ( is.st_mode != was.st_mode ) {
        sprintf(cmpmsg,"File mode changed (was 0%03o)",was.st_mode);
        return cmpmsg;
    }

    // DID THE OWNERSHIP OF THE FILE CHANGE?
    if ( is.st_uid != was.st_uid ) {
        if ( !(pw = getpwuid(was.st_uid)) )
            sprintf(cmpmsg,"File ownership has changed (was uid %d)",
                was.st_uid);
        else
            sprintf(cmpmsg,"File ownership has changed (was %s)",
                pw->pw_name);
        return cmpmsg;
    }

    // DID THE GROUP CHANGE?
    if ( is.st_gid != was.st_gid ) {
        if ( !(gr = getgrgid(was.st_gid)) )
            sprintf(cmpmsg,"Group ownership changed (was gid %d)",
                was.st_gid);
        else
            sprintf(cmpmsg,"Group ownership changed (was %s)",
                gr->gr_name);
        return cmpmsg;
    }

    // DID THE NUMBER OF LINKS TO THIS FILE CHANGE?
    if ( is.st_nlink != was.st_nlink ) {
        sprintf(cmpmsg,"Number of links changed (was %ld)",
            (long)was.st_nlink);
        return cmpmsg;
    }

    return NULL;
}

////////////////////////////////////////////////////////////
// UPDATE DATABASE OR CHECK AGAINST DATABASE :
////////////////////////////////////////////////////////////

void
Process(InoDb &inodb,const char *fullpath,struct stat &sbuf) {
    struct stat pbuf;
    InoDb::Key key;
    char *msg;

    if ( !strcmp(fullpath,"/proc") )
        return;             // Ignore pseudo directories

    if ( lstat(fullpath,&sbuf) == -1 ) {
        fprintf(stderr,"%s: stat(%s)\n",
            strerror(errno),fullpath);
        rc |= 4;            // Error, but non-fatal
        return;
    }

    // READY THE DATABASE KEY:
    key.st_dev = sbuf.st_dev;
    key.st_ino = sbuf.st_ino;

    if ( !cmdopt_c ) {
        // CREATE or UPDATE DB RECORD:
        inodb.replaceKey(key,sbuf);
    } else {
        // LOOKUP LAST SNAPSHOT :
        try {
            inodb.fetchKey(key,pbuf);
        } catch ( int e ) {
            if ( e == ENOENT ) {
                fprintf(stderr,"New %s: %s\n",
                    S_ISDIR(sbuf.st_mode)
                        ? "directory"
                        : "object",
                    fullpath);
                return;
            } else {
                fprintf(stderr,"%s: fetchKey(%s)\n",
                    strerror(e),fullpath);
                abort();       // Fatal DB error
            }
        }

        // COMPARE CURRENT STAT VS STORED STAT INFO :
        msg = Compare(sbuf,pbuf);
        if ( msg ) {
            printf("%s: %s\n",msg,fullpath);
            rc |= 8;
        }
    }
}

////////////////////////////////////////////////////////////
// WALK A DIRECTORY :
////////////////////////////////////////////////////////////

void
walk(InoDb &inodb,const char *dirname,int inclDir=0) {
    Dir dir;
    char *ent;
    long pathmax;
    struct stat sbuf;

    // AVOID CERTAIN PSEUDO FILE SYSTEMS :
    if ( !strcmp(dirname,"/proc") )
        return;

    if ( cmdopt_v )
        fprintf(stderr,"Examining: %s\n",dirname);

    // OPEN DIRECTORY :
    try {
        dir.open(dirname);
    } catch ( int e ) {
        fprintf(stderr,"%s: opening directory %s\n",
            strerror(e),dirname);
        rc |= 2;
        return;                 // Non-fatal
    }

    // INCLUDE TOP LEVEL DIRECTORIES :
    if ( inclDir )
        Process(inodb,dirname,sbuf);

    // DETERMINE MAXIMUM PATHNAME LENGTH :
    if ( (pathmax = pathconf(dirname,_PC_PATH_MAX)) == -1L ) {
        fprintf(stderr,"%s: pathconf('%s',_PC_PATH_MAX)\n",
            strerror(errno),dirname);
        abort();
    }

    char fullpath[pathmax+1];   // Full pathname
    int bx;                     // Index to basename

    strcpy(fullpath,dirname);
    bx = strlen(fullpath);
    if ( bx > 0 && fullpath[bx-1] != '/' ) {
        strcat(fullpath,"/");   // Append slash
        ++bx;                   // Adjust basename index
    }

    // PROCESS ALL DIRECTORY ENTRIES:
    while ( (ent = dir.read()) ) {
        if ( !strcmp(ent,".") || !strcmp(ent,"..") )
            continue;           // Ignore these
        strcpy(fullpath+bx,ent);

        Process(inodb,fullpath,sbuf);

        // IF OBJECT IS A DIRECTORY, DESCEND INTO IT:
        if ( S_ISDIR(sbuf.st_mode) )
            walk(inodb,fullpath);
    }

    // CLOSE DIRECTORY:
    dir.close();
}

////////////////////////////////////////////////////////////
// PROVIDE USAGE INSTRUCTIONS :
////////////////////////////////////////////////////////////

static void
usage(char *cmd) {
    char *bname = Basename(cmd);

    printf("Usage:  %s [-c] [-i] [-v] [-h] [dir...]\n",bname);
    puts("where:");
    puts("    -c      Check snapshot against file system");
    puts("    -i      (Re)Initialize the database");
    puts("    -v      Verbose");
    puts("    -h      Help (this info)");
}

////////////////////////////////////////////////////////////
// MAIN PROGRAM :
////////////////////////////////////////////////////////////

int
main(int argc,char **argv) {
    InoDb inodb;
    int optch;
    const char cmdopts[] = "hicv";

    // PROCESS COMMAND LINE OPTIONS:
    while ( (optch = getopt(argc,argv,cmdopts)) != -1 )
        switch ( optch ) {
        case 'i' :
            cmdopt_i = 1;   // -i (initialize database)
            break;
        case 'c' :          // -c (check snapshot)
            cmdopt_c = 1;
            break;
        case 'v' :
            cmdopt_v = 1;   // -v (verbose)
            break;
        case 'h' :          // -h (give help)
            cmdopt_h = 1;
            break;
        default :
            rc = 1;
        }

    if ( cmdopt_i && cmdopt_c ) {
        fputs("You cannot use -i and -c together\n",stderr);
        exit(1);
    }

    if ( cmdopt_h || rc ) {
        usage(argv[0]);
        exit(rc);
    }

    // IF -i THEN DELETE DATABASE, TO RECREATE
    if ( cmdopt_i && unlink("snapshot.db") == -1 )
        if ( errno != ENOENT ) {
            fprintf(stderr,"%s: unlink(snapshot.db)\n",
                strerror(errno));
            exit(13);
        }

    // OPEN EXISTING DATABASE (snapshot.db) :
    try {
        inodb.open("snapshot");
    } catch ( int e ) {
        // IF -c OPTION, DO NOT CREATE DB :
        if ( !cmdopt_c && e == EIO ) {
            // FILE NOT FOUND: CREATE DATABASE
            try {
                inodb.open("snapshot",O_RDWR|O_CREAT);
            } catch ( int e ) {
                fprintf(stderr,"%s: creating snapshot db\n",
                    strerror(e));
                exit(1);
            }
        } else {
            // REPORT DB OPEN ERROR :
            fprintf(stderr,"%s: creating snapshot db\n",strerror(e));
            exit(1);
        }
    }

    // WALK ALL DIRECTORIES GIVEN ON COMMAND LINE :
    for ( int x=optind; x<argc; ++x )
        walk(inodb,argv[x],1);

    inodb.close();

    return rc;
}

// End SnapShot.cc
