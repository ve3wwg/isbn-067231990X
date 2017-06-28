/* semchown.c */

#include "semop.h"

static uid_t
srch_uid(const char *user_id) {
    struct passwd *pw = getpwnam(user_id);

    if ( !pw )
        return (uid_t)(-1);
    return pw->pw_uid;
}

void
ctl_chown(int optch,const char *user_id) {
    uid_t uid = srch_uid(user_id);

    if ( uid == (uid_t)(-1) ) {
        fprintf(stderr,"Unknown userid: -%c %s\n",optch,user_id);
        exit(1);
    }

    sembuf.sem_perm.uid = uid;  /* Change userid */

    /* Cheat: change uid by using ctl_chmod() */
    ctl_chmod(optch,sembuf.sem_perm.mode);
}

static gid_t
srch_gid(const char *group_id) {
    struct group *gr = getgrnam(group_id);

    if ( !gr )
        return (gid_t)(-1);
    return gr->gr_gid;
}

void
ctl_chgrp(int optch,const char *group) {
    gid_t gid = srch_gid(group);

    if ( gid == (gid_t)(-1) ) {
        fprintf(stderr,"Unknown group: -%c %s\n",optch,group);
        exit(1);
    }

    sembuf.sem_perm.gid = gid;  /* Change group */

    /* Cheat: change gid by using ctl_chmod() */
    ctl_chmod(optch,sembuf.sem_perm.mode);
}
