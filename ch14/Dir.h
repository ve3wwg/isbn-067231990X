// dir.h

#ifndef _dir_h_
#define _dir_h_

#include <sys/types.h>
#include <dirent.h>

////////////////////////////////////////////////////////////
// A Directory class object :
////////////////////////////////////////////////////////////

class Dir {
    DIR     *dir;
    char    *name;
    int     error;
public:
    Dir();
    ~Dir();
    Dir &open(const char *path);
    Dir &rewind();
    Dir &close();
    char *read();
    inline int getError() { return error; }
    inline char *getEntry() { return name; }
};

#endif // _dir_h_

// End dir.h
