// msq.h :
//
// Message Queue Class :

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct Msg {
    long    msgtyp;     // Message type/priority
};

class Msq {
    enum state { ready, notReady };
    key_t   key;        // IPC Key
    int     msqid;      // IPC ID
    int     error;      // Last errno

protected:
    void _verify(state s);

public:
    Msq();
    Msq &create(key_t key,int flags);
    Msq &access(key_t key);
    Msq &dispose();
    Msq &destroy();
    msqid_ds &stat(msqid_ds &stbuf);
    Msq &change(msqid_ds &stbuf);
    int send(Msg &msg,size_t size,int flags=0);
    int recv(Msg &msg,size_t &size,size_t maxsz,long msgtyp,int flags=0);
    inline int getError() { return error; }
    inline key_t getKey() { return key; }
};

// End msq.h 
