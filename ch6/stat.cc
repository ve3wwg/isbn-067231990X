// stat.cc

#include <iostream.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>


////////////////////////////////////////////////////////////
// Simple Stat object :
////////////////////////////////////////////////////////////

class Stat : public stat {

private:
    char        *path;          // Pathname
    int         fd;             // File descriptor

public:
    Stat() { path = 0; fd = -1; }
    ~Stat();

    Stat & examine(const char *pathname);
    Stat & examine(int fd);
    int operator==(Stat &o);

    friend ostream & operator<<(ostream &out,Stat &o);
};

////////////////////////////////////////////////////////////
// Destructor :
////////////////////////////////////////////////////////////

Stat::~Stat() {
    if ( path )                 // Path allocated?
        delete path;            // Yes, release string
}

////////////////////////////////////////////////////////////
// stat(2) on pathname :
////////////////////////////////////////////////////////////

Stat &
Stat::examine(const char *pathname) {

    if ( path )                 // Is there a prior path?
        delete path;            // Yes, release string

    path = strdup(pathname);    // Create a new string
    fd = -1;                    // Not using fd here

    // Obtain stat info :
    if ( ::stat(path,this) == -1 )
        throw errno;            // Oops- error

    return *this;               // Successful
}

////////////////////////////////////////////////////////////
// Perform fstat(2) on fd :
////////////////////////////////////////////////////////////

Stat &
Stat::examine(int fd) {

    if ( path ) {               // Is there a path?
        delete path;            // Yes, release string
        path = 0;               // Mark as gone
    }

    this->fd = fd;              // Save fd

    // Obtain stat info :
    if ( ::fstat(fd,this) == -1 )
        throw errno;            // Oops- error

    return *this;               // Successful
}

////////////////////////////////////////////////////////////
// This friend function can be called to dump the
// contents of the stat structure :
////////////////////////////////////////////////////////////

ostream &
operator<<(ostream &out,Stat &o) {

    // If there is no information, say so :
    if ( o.fd == -1 && !o.path ) {
        out << "No current information.";
        return out;
    }

    // Otherwise, show what sort of stat() info it is:
    if ( o.path )
        cout << "stat(" << o.path << ") {\n";
    else
        cout << "fstat(" << o.fd << ") {\n";

    // Dump all other structure members :

    cout<< "\tst_dev =\t" << o.st_dev << ";\n"
        << "\tst_ino =\t" << o.st_ino << ";\n";

    cout.setf(ios::oct,ios::basefield);
    cout<< "\tst_mode =\t" << '0' << o.st_mode << ";\n";

    cout.setf(ios::dec,ios::basefield);
    cout<< "\tst_nlink =\t" << o.st_nlink << ";\n"
        << "\tst_uid =\t" << o.st_uid << ";\n"
        << "\tst_gid =\t" << o.st_gid << ";\n"
        << "\tst_rdev =\t" << o.st_rdev << ";\n"
        << "\tst_atime =\t" << o.st_atime << ";\n"
        << "\tst_mtime =\t" << o.st_mtime << ";\n"
        << "\tst_ctime =\t" << o.st_ctime << ";\n"
        << "\tst_size =\t" << o.st_size << ";\n"
        << "\tst_blocks =\t" << o.st_blocks << ";\n"
        << "\tst_blksize =\t" << o.st_blksize << ";\n"
        << "\tst_flags =\t" << o.st_flags << ";\n"
        << "\tst_gen = \t" << o.st_gen << ";\n"
        << "\n};";

    return out;
}

////////////////////////////////////////////////////////////
// This method tests to see if two file system objects
// are the same one :
////////////////////////////////////////////////////////////

int
Stat::operator==(Stat &o) {

    // Does either object lack information?

    if ( fd == -1 && !path )
        throw EINVAL;               // No information here
    if ( o.fd == -1 && !path )
        throw EINVAL;               // No information there

    // Now test to see if these are the same objects:
    
    if ( o.st_dev != st_dev         // Devices match?
    ||   o.st_ino != st_ino )       // Inodes match?
        return 0;                   // Devices or inodes don't match

    return 1;                       // Return TRUE, they are the same
}

////////////////////////////////////////////////////////////
// Test Main Program :
////////////////////////////////////////////////////////////

int
main(int argc,char **argv) {
    int x;                          // work index
    Stat t;                         // stat("./stat")
    Stat s;                         // work stat object
    
    t.examine("./stat");            // Do stat(2)

    // Now try all command line arguments :

    for ( x=1; x<argc; ++x ) {

        try {
            s.examine(argv[x]);     // Stat this pathname
        } catch ( int e ) {
            // e is errno value :
            cerr << strerror(e) << ": stat(2) of "
                << argv[x] << '\n';
            continue;
        }

        cout << s << '\n';          // Dump stat info

        // Test if s is same as t :

        cout << "'" << argv[x] << "' is "
            << ( s == t ? "same" : "not the same" )
            << " file as ./stat\n";
    }

    return 0;
}

// End stat.cc
