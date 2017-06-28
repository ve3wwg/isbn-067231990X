/* usage.c */

#include "semop.h"

/*
 * Display usage instructions :
 */
void
usage(void) {

    puts("Usage:  semop [options]");
    puts("Options:");
    puts("\t-k key\tIPC Key for -a or -c option.");
    puts("\t-a\t\tAccess existing set based on -k key");
    puts("\t-c n\t\tCreate set of n semaphores using -k key");
    puts("\t-i ID\t\tAccess existing set by IPC ID");
    puts("\t-o <sops>\tsemop(n) for wait/zero/notify");
    puts("\t-s\t\tsemctl(IPC_STAT)");
    puts("\t-m mode\t\tsemctl(IPC_SET) with new permissions");
    puts("\t-x userid\tsemctl(IPC_SET) with new userid");
    puts("\t-y group\tsemctl(IPC_SET) with new group");
    puts("\t-d\t\tsemctl(IPC_RMID)");
    puts("\t-g n\t\tsemctl(GETVAL) for semaphore n");
    puts("\t-G\t\tsemctl(GETALL)");
    puts("\t-v n=x\t\tsemctl(SETVAL) set semaphore n to x");
    puts("\t-V m,n,o\tsemctl(SETALL)");
    puts("\t-p n\t\tsemctl(GETPID) for semaphore n");
    puts("\t-P\t\tReport semctl(GETPID) for all semaphores");
    puts("\t-n x\t\tsemctl(GETNCNT) for semaphore x");
    puts("\t-z x\t\tsemctl(GETZCNT) for semaphore x");
    puts("\t-u\t\tNo SEM_UNDO (default)");
    puts("\t-U\t\tUse SEM_UNDO");
    puts("\t-R\t\tReport SEM_UNDO flags");
    puts("\n<sops> :");
    puts("\t<semaphore#>=<semop>[{u|U}],...");
    puts("where:");
    puts("\t<semaphore#>\tIs the semaphore # (starting from zero)");
    puts("\t<semop>\t\tSemaphore operation: -n, 0 or +n");
    puts("\t\t\tNegative waits, Postive notifies");
    puts("\t\t\twhile zero waits for zero.");
    puts("\tu\t\tDo not use SEM_UNDO");
    puts("\tU\t\tApply SEM_UNDO");
    puts("\tExample: -o 0=-4U,2=+1u,1=2");
}
