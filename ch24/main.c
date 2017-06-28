/* main.c */

#include "semop.h"

int semid = -1;             /* No default IPC ID */
int n_sem = 3;              /* Default # semaphores in a set */

/*
 * semop utility main program :
 *
 * Use './semop -h' for help.
 */
int
main(int argc,char **argv) {
    int z;                      /* Option character/status */
    int x;                      /* Iterator */
    int rc = 0;                 /* Return code */
    int n;                      /* # of values in array */
    key_t key = 0xFEEDF00D;     /* Default IPC key */
    int sems[MAX_NSET];         /* Array of semaphore numbers */
    int array[MAX_NSET];        /* Array of integer values */
    int flags[MAX_NSET];        /* Flags for each semaphore */
    unsigned long ul;           /* unsigned value */
    const char cmdopts[] = "hk:ac:i:o:sm:dg:Gv:V:p:Pn:z:uURx:y:";

    for ( x=0; x<MAX_NSET; ++x )
        flags[x] = 0;           /* Initialize with no SEM_UNDO */

    while ( !rc && (z = getopt(argc,argv,cmdopts)) != -1 )
        switch ( z ) {
        case 'h' :              /* -h           ; usage info */
            usage();
            return 0;

        case 'k' :              /* -k IPCkey[,n] ; IPC Key, n_sem */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            key = (key_t) ul;
            break;

        case 'a' :              /* -a           ; access set */
            get_set(z,key,0);   /* Locate IPC ID */
            ctl_stat(z,-1);     /* Just fill sembuf & fix n_sem */
            printf("  There are %d semaphores in this set.\n",
                n_sem);
            break;

        case 'c' :              /* -c n         ; create set */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            n_sem = (int)ul;
            get_set(z,key,1);   /* Create set */
            ctl_stat(z,0);      /* Just fill sembuf */
            printf("  -c %d : Created semaphore set -k 0x%08lX\n",
                n_sem,(long)key);
            break;

        case 'i' :              /* -i IPCID     ; IPC ID     */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            semid = (int) ul;
            ctl_stat(z,-1);     /* Just report failure */
            printf("  -i %d : There are %d semaphores in this set.\n",
                semid,n_sem);
            break;

        case 'o' :              /* -o m[,n[,o]] ; semop(2)   */
            if ( (n = cvt2semops(optarg,sems,array,flags)) < 1 )
                goto badcvt;
            ctl_semop(z,optarg,sems,array,flags,n);
            break;

        case 's' :              /* -s           ; IPC_STAT   */
            ctl_stat(z,1);
            break;

        case 'm' :              /* -m mode      ; IPC_SET    */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            ctl_chmod(z,(mode_t)ul);
            break;

        case 'x' :              /* -x userid    ; IPC_SET    */
            ctl_chown(z,optarg);
            break;

        case 'y' :              /* -g group     ; IPC_SET    */
            ctl_chgrp(z,optarg);
            break;

        case 'd' :              /* -d           ; IPC_RMID   */
            ctl_rmid(z);
            break;

        case 'g' :              /* -g n         ; IPC_GETVAL */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            ctl_getval(z,(int)ul);
            break;

        case 'G' :              /* -G           ; IPC_GETALL */
            ctl_getall(z);
            break;

        case 'v' :              /* -v n=x       ; IPC_SETVAL */
            if ( (n = cvt2array(optarg,array,"=")) != 2 )
                goto badcvt;
            ctl_setval(z,array[0],array[1]);
            break;

        case 'V' :              /* -V m,n,o     ; IPC_SETALL */
            if ( (n = cvt2array(optarg,&array[0],",")) != n_sem )
                goto badcvt;
            ctl_setall(z,array);
            break;

        case 'p' :              /* -p n         ; GETPID */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            ctl_get(z,GETPID,(int)ul);
            break;

        case 'P' :
            for ( x=0; x<n_sem; ++x )
                ctl_get('p',GETPID,x);
            break;

        case 'n' :              /* -n           ; GETNCNT */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            ctl_get(z,GETNCNT,(int)ul);
            break;

        case 'z' :              /* -z           ; GETZCNT */
            if ( cvt2ulong(optarg,&ul) )
                goto badcvt;
            ctl_get(z,GETZCNT,(int)ul);
            break;

        case 'u' :              /* -u           ; No SEM_UNDO */
            for ( x=0; x<n_sem; ++x )
                flags[x] &= ~SEM_UNDO;
            report(z,key,flags);
            break;

        case 'U' :              /* -U           ; SEM_UNDO   */
            for ( x=0; x<n_sem; ++x )
                flags[x] |= SEM_UNDO;
            report(z,key,flags);
            break;

        case 'R' :
            report(z,key,flags);
            break;

        default  :              /* Unknown option */
            rc = 1;
        }

    /*
     * Command line arguments are ignored :
     */
    for ( ; optind < argc; ++optind, rc=2 )
        printf("Ignored argument '%s'\n",argv[optind]);

    return rc;

    /*
     * Bad numeric conversion :
     */
badcvt:
    fprintf(stderr,"Bad numeric: -%c %s\n",z,optarg);
    return 1;
}
