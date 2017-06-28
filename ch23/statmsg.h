// statmsg.h 

struct StatMsg : Msg {
    enum {
        stat,                   // stat a pathname
        lstat,                  // lstat a pathname
        stop                    // stop the server
    }           request;        // Request type
    int         error;          // zero if successful
    pid_t       PID;            // Requesting Process ID
    union {
        char    path[256];      // Pathname to stat
        struct stat stbuf;      // stat(2) or lstat(2) info
    }           u;              // union
};

// End statmsg.h
