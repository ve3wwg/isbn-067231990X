// Dbm.cc

#include <string.h>
#include <errno.h>
#include "Dbm.h"

////////////////////////////////////////////////////////////
// Constructor :
////////////////////////////////////////////////////////////

Dbm::Dbm() {
    flags = 0;              // No flags
    path = 0;               // No path
    db = 0;                 // No database
    error = 0;              // No logged errors
}

////////////////////////////////////////////////////////////
// Destructor :
////////////////////////////////////////////////////////////

Dbm::~Dbm() {
    if ( db )
        close();            // Close database
}

////////////////////////////////////////////////////////////
// Open/Create a Database :
// NOTES:
//  flags       O_RDWR, O_RDONLY, O_CREAT etc. (see open(2))
//  mode        Permission bits
////////////////////////////////////////////////////////////

Dbm &
Dbm::open(const char *path,int flags,int mode) {

    if ( db )
        throw error = EPERM;    // Database already open

    db = ::dbm_open(path,this->flags = flags,mode);
    if ( !db )
        throw error = EIO;      // Open failed

    path = strdup(path);        // Save pathname

    return *this;
}

////////////////////////////////////////////////////////////
// Close the open database :
////////////////////////////////////////////////////////////

Dbm &
Dbm::close() {

    if ( !db )
        throw error = EPERM;    // Database is not open

    dbm_close(db);              // Close Database
    db = 0;
    delete path;                // Free pathname
    path = 0;

    return *this;
}

////////////////////////////////////////////////////////////
// Fetch data by key :
////////////////////////////////////////////////////////////

datum
Dbm::fetch(datum key) {
    datum content;

    if ( !db )
        throw error = EPERM;    // No database

    content = ::dbm_fetch(db,key);
    if ( dbm_error(db) ) {
        dbm_clearerr(db);
        throw error = EIO;
    }
    if ( !content.dptr )
        throw error = ENOENT;   // Not found

    return content;             // Found content
}

////////////////////////////////////////////////////////////
// Replace or Insert new data by key :
////////////////////////////////////////////////////////////

Dbm &
Dbm::store(datum key,datum content,int flags) {

    if ( !db )
        throw error = EPERM;    // No database

    if ( ::dbm_store(db,key,content,flags) < 0 ) {
        dbm_clearerr(db);
        throw error = EIO;      // Failed
    }
    return *this;
}

////////////////////////////////////////////////////////////
// Delete data by key :
////////////////////////////////////////////////////////////

Dbm &
Dbm::deleteKey(datum key) {

    if ( !db )
        throw error = EPERM;    // No database
    if ( ::dbm_delete(db,key) < 0 ) {
        dbm_clearerr(db);
        throw error = EIO;      // Failed
    }
    return *this;
}

////////////////////////////////////////////////////////////
// Retrieve the first data key :
////////////////////////////////////////////////////////////

datum
Dbm::firstKey() {
    datum d;

    if ( !db )
        throw error = EPERM;    // No database

    d = ::dbm_firstkey(db);

    if ( dbm_error(db) ) {
        dbm_clearerr(db);
        throw error = EIO;      // Database error
    }

    return d;
}

////////////////////////////////////////////////////////////
// Retrieve the next data key :
////////////////////////////////////////////////////////////

datum
Dbm::nextKey() {
    datum d;

    if ( !db )
        throw error = EPERM;    // No database

    d = ::dbm_nextkey(db);

    if ( dbm_error(db) ) {
        dbm_clearerr(db);
        throw error = EIO;      // Database error
    }

    return d;
}

// End Dbm.cc
