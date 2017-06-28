// passwd.h

#include <sys/types.h>
#include <pwd.h>

class Passwd : public passwd {
    enum {
        undefined,                  // object has no content
        defined                     // object has content
    }       state;                  // This object's state
    int     e;                      // Last errno
protected:
    void _dispose();                // Dispose of current content
    void _import(struct passwd *p); // Import new contents
public:
    Passwd()                        // Constructor
        { state = undefined; e = 0; }
    ~Passwd()                       // Destructor
        { _dispose(); }
    inline int isValid()
        { return state == defined ? 1 : 0; }
    inline int getError()           // Get errno value
        { return e; }
    char *getuid(uid_t uid);        // Lookup uid, return name
    int getnam(const char *name);   // Lookup name, return Boolean
};

// End passwd.h
