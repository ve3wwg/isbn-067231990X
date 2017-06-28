/* globget.c */

#include "globvar.h"

/*
 * Return the string pointer for a variable's value :
 */
char *
get_var(const char *varname) {
    char *cp;                   /* Scanning pointer */
    int nlen = strlen(varname); /* Length of variable name */

    for ( cp = &globvars->vars[0]; *cp; cp += strlen(cp) + 1 )
        if ( !strncmp(varname,cp,nlen) && cp[nlen] == '=' ) 
            return cp + nlen + 1; /* Pointer to it's value */

    return NULL;                /* Variable not found */
}
