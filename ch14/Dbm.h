// Dbm.h

#ifndef _Dbm_h_
#define _Dbm_h_

#include <sys/types.h>
#include <unistd.h>
#include <ndbm.h>
#include <fcntl.h>

////////////////////////////////////////////////////////////
// A Class for the DBM Routines :
////////////////////////////////////////////////////////////

class Dbm {
    int     flags;          // Open flags
    char    *path;          // Pathname of database
    DBM     *db;            // Open database
protected:
    int     error;          // Last error
public:
    Dbm();
    ~Dbm();
    Dbm &open(const char *path,int flags=O_RDWR,int mode=0666);
    Dbm &close();
    datum fetch(datum key);
    Dbm &store(datum key,datum content,int flags);
    Dbm &deleteKey(datum key);
    datum firstKey();
    datum nextKey();
    inline int getError() { return error; }
    inline int getFlags() { return flags; }
    inline char *getPath() { return path; }
};

#endif // _Dbm_h_

// End Dbm.h
