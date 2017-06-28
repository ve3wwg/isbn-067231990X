// import.cc

#include "passwd.h"
#include <string.h>

extern "C" char *strdup(const char *str);

////////////////////////////////////////////////////////////
// DISPOSE OF OBJECT'S CONTENTS (IF ANY):
//      1. Check state (if defined)
//      2. Delete all allocated strings
//      3. Set state to "undefined"
////////////////////////////////////////////////////////////

void
Passwd::_dispose() {
    if ( state == defined ) {
        delete pw_name;     pw_name = 0;
        delete pw_passwd;   pw_passwd = 0;
        delete pw_gecos;    pw_gecos = 0;
        delete pw_dir;      pw_dir = 0;
        delete pw_shell;    pw_shell = 0;
    }
    state = undefined;
}

////////////////////////////////////////////////////////////
// IMPORT A STRUCT PW INTO THIS OBJECT :
//      1. Dispose of current contents
//      2. Copy and strdup(3) member components
//      3. Set state to "defined"
////////////////////////////////////////////////////////////

void
Passwd::_import(passwd *pw) {

    if ( state == defined )
        _dispose();                 // Dispose of present content

    pw_name = strdup(pw->pw_name);
    pw_passwd = strdup(pw->pw_passwd);
    pw_uid = pw->pw_uid;
    pw_gid = pw->pw_gid;
    pw_gecos = strdup(pw->pw_gecos);
    pw_dir = strdup(pw->pw_dir);
    pw_shell = strdup(pw->pw_shell);

    state = defined;                // Set into defined state
}

// End import.cc
