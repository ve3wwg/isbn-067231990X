// InoDb.h

#ifndef _InoDb_h_
#define _InoDb_h_

#include <sys/types.h>
#include <sys/stat.h>
#include "Dbm.h"

////////////////////////////////////////////////////////////
// Specialized Database Class for an Inode Database :
////////////////////////////////////////////////////////////

class InoDb : public Dbm {
public:
    struct Key {
        dev_t   st_dev;     // Device number
        ino_t   st_ino;     // Inode number
    };
protected:
    Key         ikey;       // Internal key
public:
    InoDb &fetchKey(Key &key,struct stat &sbuf);
    InoDb &insertKey(Key &key,struct stat &sbuf);
    InoDb &replaceKey(Key &key,struct stat &sbuf);
    InoDb &deleteKey(Key &key);
    Key *firstKey();
    Key *nextKey();
};

#endif _InoDb_h_

// End InoDb.h
