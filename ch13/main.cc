// main.cc

#include <iostream.h>
#include <string.h>
#include "passwd.h"

int
main(int argc,char **argv) {
    unsigned ux;
    Passwd pw;
    const char *accts[] = { "uucp", "xyzzy", "games" };

    (void) argc;
    (void) argv;

    // Report root's home directory :

    try {
        pw.getuid(0);           // Lookup root
        cout << "Root's home dir is " << pw.pw_dir << ".\n";
    } catch ( int e ) {
        cerr << strerror(e) << ": looking up uid(0)\n";
    }

    // Try a few accounts :

    for ( ux=0; ux<sizeof accts/sizeof accts[0]; ++ux )
        try {
            pw.getnam(accts[ux]);   // Lookup account
            cout << "Account " << accts[ux]
                << " uses the shell " << pw.pw_shell << ".\n";
        } catch ( int e ) {
            cerr << strerror(e) << ": looking up account "
                << accts[ux] << ".\n";
        }

    return 0;
}
