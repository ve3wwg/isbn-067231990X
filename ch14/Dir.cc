// dir.cc

#include "Dir.h"
#include <errno.h>
#include <string.h>

extern "C" char *strdup(const char *str);

////////////////////////////////////////////////////////////
// Dir Constructor :
////////////////////////////////////////////////////////////

Dir::Dir() {
    dir = 0;
    name = 0;
}

////////////////////////////////////////////////////////////
// Dir Destructor :
////////////////////////////////////////////////////////////

Dir::~Dir() {
    if ( dir ) 
        close();
}

////////////////////////////////////////////////////////////
// Open a directory :
////////////////////////////////////////////////////////////

Dir &
Dir::open(const char *path) {

    if ( dir )
        throw error = EINVAL;   // Object is already open

    dir = ::opendir(path);      // Attempt to open directory
    if ( !dir )
        throw error = errno;    // Open failed

    return *this;
}

////////////////////////////////////////////////////////////
// Close a directory :
////////////////////////////////////////////////////////////

Dir &
Dir::close() {
    int z;

    if ( !dir )
        throw error = EINVAL;   // Nothing to close
    if ( name ) {
        delete name;
        name = 0;               // No name now
    }
    z = ::closedir(dir);
    dir = 0;                    // No dir now
    if ( z == -1 )
        throw error = errno;
    return *this;
}

////////////////////////////////////////////////////////////
// Read a directory :
////////////////////////////////////////////////////////////

char *
Dir::read() {
    dirent *p;

    if ( !dir )
        throw error = EINVAL;   // Nothing to read
    if ( name ) {
        delete name;
        name = 0;
    }

    p = readdir(dir);           // Read the next entry
    if ( !p )
        return name;            // End of directory

    return name = strdup(p->d_name);
}

////////////////////////////////////////////////////////////
// Rewind a directory :
////////////////////////////////////////////////////////////

Dir &
Dir::rewind() {

    if ( !dir )
        throw error = EINVAL;   // Nothing to rewind
    ::rewinddir(dir);           // Rewind directory
    return *this;
}

// End dir.cc
