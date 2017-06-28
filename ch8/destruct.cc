// destruct.cc

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

extern "C" {
    extern char *tempnam(const char *tmpdir,const char *prefix);
}

////////////////////////////////////////////////////////////
// A demonstration class, showing how a temp file can
// be used within a C++ class, with automatic
// destruction.
////////////////////////////////////////////////////////////

class Temp {
    char    *tf_path;           // Temp. File Pathname
    FILE    *tf;                // Open temp. file
public:
    Temp();                     // Constructor
    ~Temp();                    // Destructor
    Temp &printf(const char *format,...);
    Temp &rewind();             // Rewind
    Temp &gets(char *buf,int bufsiz);
};


////////////////////////////////////////////////////////////
// Constructor :
////////////////////////////////////////////////////////////

Temp::Temp() {

    /*
     * Create a temp. file pathname :
     */
    if ( !(tf_path = tempnam("/tmp","tmp-")) )
        throw errno;            // Temp. file generation failed

    /*
     * Create, open and write to the temp. file :
     */
    if ( !(tf = fopen(tf_path,"w+")) )
        throw errno;            // Open failed

    printf("Created temp file: %s\n",tf_path);
}

////////////////////////////////////////////////////////////
// Destructor :
////////////////////////////////////////////////////////////

Temp::~Temp() {
    fclose(tf);                 // Close the open file
    unlink(tf_path);            // Delete the temp file
    delete tf_path;             // Free pathname string

    write(1,"Temp::~Temp() called.\n",22);
}

////////////////////////////////////////////////////////////
// The printf() method :
//
// Allows the caller to write to the temp. file with the
// convenience of printf().
////////////////////////////////////////////////////////////

Temp &
Temp::printf(const char *format,...) {
    va_list ap;

    va_start(ap,format);
    vfprintf(tf,format,ap);
    va_end(ap);

    return *this;
}


////////////////////////////////////////////////////////////
// Rewind the temp. file :
////////////////////////////////////////////////////////////

Temp &
Temp::rewind() {
    ::rewind(tf);               // Rewind the temp file
    return *this;
}

////////////////////////////////////////////////////////////
// Read back one text line from the temp. file :
////////////////////////////////////////////////////////////

Temp &
Temp::gets(char *buf,int bufsiz) {
    int e;

    if ( !fgets(buf,bufsiz,tf) ) {
        if ( feof(tf) )         // EOF ?
            throw EOF;          // Indicate EOF
        e = errno;
        clearerr(tf);
        throw e;                // Throw the error
    }

    return *this;
}

////////////////////////////////////////////////////////////
// Main program :
////////////////////////////////////////////////////////////

int
main(int argc,char *argv[]) {
    Temp tf;                    // Create a temp file
    char buf[256];

    (void) argc;
    (void) argv;

    // Announce start of program :
    printf("PID %ld started:\n",(long)getpid());

    // Now write one text line to the temp file :
    tf.printf("PID %ld was here.\n",(long)getpid());

    tf.rewind();                // Rewind temp file

    // Now read back the one text line from the temp file

    try {
        tf.gets(buf,sizeof buf);
    } catch ( int e ) {
        fprintf(stderr,"%s: tf.gets()\n",strerror(e));
        exit(1);
    }

    printf("Read back: %s\n",buf);

    puts("Now exiting..");
    return 0;
}

// End destruct.cc
