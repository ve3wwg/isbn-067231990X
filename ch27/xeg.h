/* xeg.h */

#include <stdio.h>
#include <strings.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

typedef unsigned long Ulong;

#define B1      1           /* Left button */
#define B2      2           /* Middle button */
#define B3      4           /* Right button */

extern Display *disp;       /* Display */
extern int scr;             /* Screen */

extern Ulong bg;            /* Background color */
extern Ulong fg;            /* Foreground color */

extern Ulong wht;           /* White */
extern Ulong blk;           /* Black */

extern Ulong red;           /* red */
extern Ulong green;         /* green */
extern Ulong blue;          /* blue */

extern Window xwin;         /* Drawing window */

extern void event_loop(void);

/* End xeg.h */
