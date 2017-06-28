/* dlmain.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>

extern int strcasecmp(const char *s1, const char *s2);

int
main(int argc,char **argv) {
    int isum = 0;               // Sum variable
    void *dlh = 0;              // Dynamic library handle
    int (*sum_ints)(int n,...); // Dynamic function pointer

    if ( argc <= 1 || strcasecmp(argv[1],"DONT_LOAD") != 0 ) {
        dlh = dlopen("libdyn001.so",RTLD_LAZY);
        if ( !dlh ) {
            fprintf(stderr,"%s: loading ./libdyn001.so\n",dlerror());
            return 1;
        }
    }

    sum_ints = (int (*)(int,...)) dlsym(dlh,"sum_ints");
    if ( !sum_ints ) {
        fprintf(stderr,"%s: finding symbol sum_ints()\n",dlerror());
        return 1;
    }

    /*
     * Call the dynamically loaded function :
     */
    isum = sum_ints(5,1,2,3,4,5);
    printf("isum = %d\n",isum);

    if ( dlh )
        dlclose(dlh);

    return 0;
}

/* End dlmain.c */
