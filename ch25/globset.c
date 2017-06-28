/* globset.c */

#include "globvar.h"

/*
 * Change the value of a global variable :
 */
void
set_var(const char *varname,const char *value) {
    int z;                          /* status code */
    char *var = get_var(varname);   /* Locate variable if it exists */
    char *cp;                       /* utility char pointer */
    int nlen = strlen(varname);     /* Length of variable name */
    int vlen = strlen(value);       /* Length of variable's value */
    int in_use = 0;                 /* Bytes in use */
    int avail = globvars->size;     /* Bytes available */
    
    if ( var ) {                    /* Does variable exist? */

        in_use = (int)( var - &globvars->vars[0] ) + 1;
        avail -= in_use;            /* Bytes available for new value */

        z = strlen(var + nlen + 1); /* Length of current string */
        if ( vlen > avail + z )
            goto nospc;             /* Insufficient space */

        /*
         * Now delete the variable :
         */
        var = var - nlen - 1;       /* Point to start of entry */

        for ( cp=var+strlen(var)+1; *cp; var += z, cp += z ) {
            z = strlen(cp) + 1;     /* Length of next value */
            memmove(var,cp,z);      /* Move it up */
        }

    } else {
        /*
         * Find end of global storage :
         */
        for ( var = &globvars->vars[0]; *var; var += strlen(var) + 1 )
            ;

        in_use = (int)( var - &globvars->vars[0] ) + 1;
        avail -= in_use;            /* Bytes available for new value */

        if ( nlen + 1 + vlen > avail )
            goto nospc;
    }

    /*
     * Append VARIABLE=VALUE\0 to end of shared region :
     */
    strcpy(var,varname);    /* Variable name */
    var += nlen;            /* Point past variable name */
    *var++ = '=';           /* The equal sign */
    strcpy(var,value);      /* The variable's value */
    var[vlen+1] = 0;        /* 2 null bytes mark the end */

    return;                 /* Successful */

    /*
     * Insufficient space to store this variable :
     */
nospc:
    fprintf(stderr,"%s: %s='%s'\n",strerror(ENOSPC),varname,value);
    exit(1);
}
