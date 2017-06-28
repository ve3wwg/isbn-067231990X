// InoDb.cc

#include <errno.h>
#include "InoDb.h"

////////////////////////////////////////////////////////////
// Fetch stat info by inode number :
////////////////////////////////////////////////////////////

InoDb &
InoDb::fetchKey(Key &key,struct stat &sbuf) {
    datum d, f;

    d.dptr = (char *)&key;
    d.dsize = sizeof key;
    f = fetch(d);

    if ( f.dsize != sizeof (struct stat) )
        throw error = EINVAL;   // Corrupt database
    memcpy(&sbuf,f.dptr,sizeof sbuf);

    return *this;
}

////////////////////////////////////////////////////////////
// Add new stat info by inode number :
////////////////////////////////////////////////////////////

InoDb &
InoDb::insertKey(Key &key,struct stat &sbuf) {
    datum k, c;

    k.dptr = (char *)&key;
    k.dsize = sizeof key;
    c.dptr = (char *)&sbuf;
    c.dsize = sizeof sbuf;
    store(k,c,DBM_INSERT);
    return *this;
}

////////////////////////////////////////////////////////////
// Replace stat info by inode number :
////////////////////////////////////////////////////////////

InoDb &
InoDb::replaceKey(Key &key,struct stat &sbuf) {
    datum k, c;

    k.dptr = (char *)&key;
    k.dsize = sizeof key;
    c.dptr = (char *)&sbuf;
    c.dsize = sizeof sbuf;
    store(k,c,DBM_REPLACE);
    return *this;
}

////////////////////////////////////////////////////////////
// Delete stat info by inode number :
////////////////////////////////////////////////////////////

InoDb &
InoDb::deleteKey(Key &key) {
    datum k;

    k.dptr = (char *)&key;
    k.dsize = sizeof key;
    Dbm::deleteKey(k);
    return *this;
}

////////////////////////////////////////////////////////////
// Retrieve the first key entry :
////////////////////////////////////////////////////////////

InoDb::Key *
InoDb::firstKey() {
    datum k;
    
    k = Dbm::firstKey();
    if ( !k.dptr )
        return 0;                   // Return NULL for EOF

    if ( k.dsize != sizeof ikey )
        throw error = EINVAL;       // Corrupt?
    memcpy(&ikey,k.dptr,sizeof ikey);
    return &ikey;                   // Return pointer to key
}

////////////////////////////////////////////////////////////
// Retrieve the last key entry :
////////////////////////////////////////////////////////////

InoDb::Key *
InoDb::nextKey() {
    datum k;

    k = Dbm::nextKey();
    if ( !k.dptr )
        return 0;                   // Return NULL for EOF

    if ( k.dsize != sizeof ikey )
        throw error = EINVAL;       // Corrupt?
    memcpy(&ikey,k.dptr,sizeof ikey);
    return &ikey;                   // Return pointer to key
}

// End InoDb.cc
