// EmptyDb.cc

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "InoDb.h"

////////////////////////////////////////////////////////////
// MAIN PROGRAM :
//
// If the first command line argument is the word "LIST"
// the keys will be listed only. Otherwise the records
// are deleted.
//
// This test program deletes all entries from the database
// to demonstrate key traversal and delete operations.
////////////////////////////////////////////////////////////

int
main(int argc,char **argv) {
    InoDb inodb;
    InoDb::Key *key;

    (void)argc;
    (void)argv;

    // OPEN EXISTING DATABASE (snapshot.db) :
    try {
        inodb.open("snapshot");
    } catch ( int e ) {
        fprintf(stderr,"%s: creating snapshot db",strerror(e));
        exit(1);
    }

    // LIST THE KEYS ONLY :
    if ( argc == 2 && !strcasecmp(argv[1],"LIST") ) {
        for (key=inodb.firstKey(); key != NULL;
            key=inodb.nextKey() ) {
            printf("Key %d:%d from db.\n",
                key->st_dev,key->st_ino);
        }
        return 0;
    }

    // DELETE ALL ENTRIES IN DB :
    while ( (key = inodb.firstKey()) != NULL ) {
        printf("Delete: Inode %d:%d from db.\n",
            key->st_dev,key->st_ino);
        inodb.deleteKey(*key);  // DELETE ENTRY
    }

    // CLOSE DB :
    inodb.close();

    return 0;
}

// End SnapShot.cc
