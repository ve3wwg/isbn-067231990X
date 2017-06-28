/* globun.c */

#include "globvar.h"

/*
 * Unset a variable :
 */
void
unset_var(const char *varname) {
    int z;                          /* status code */
    char *var = get_var(varname);   /* Locate variable if it exists */
    char *cp;                       /* utility char pointer */
    int nlen = strlen(varname);     /* Length of variable name */
    
    if ( !var )
        return;                     /* Variable is already unset */

    /*
     * Now delete the variable :
     */
    var = var - nlen - 1;       /* Point to start of entry */

    for ( cp=var+strlen(var)+1; *cp; var += z, cp += z ) {
        z = strlen(cp) + 1;     /* Length of next value */
        memmove(var,cp,z);      /* Move it up */
    }

    *var = 0;                   /* two nulls mark the end of vars */

    return;                     /* Successful */
}
