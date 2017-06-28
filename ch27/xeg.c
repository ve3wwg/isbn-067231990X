/* xeg.c */

#include "xeg.h"

Display *disp;              /* Display */
int scr;                    /* Screen */

Ulong bg;                   /* Background color */
Ulong fg;                   /* Foreground color */

Ulong wht;                  /* White */
Ulong blk;                  /* Black */

Ulong red;                  /* red */
Ulong green;                /* green */
Ulong blue;                 /* blue */

Window xwin;                /* Drawing window */

int
main(int argc,char **argv) {
    Colormap cmap;          /* Color map */
    XColor approx;          /* Approximate color */
    XColor exact;           /* Precise color */
    XSizeHints hint;        /* Initial size hints */

    /*
     * Open display (connection to X Server) :
     */
    if ( !(disp = XOpenDisplay(NULL)) ) {
        fprintf(stderr,"Cannot open display: check DISPLAY variable\n");
        exit(1);
    }

    scr = DefaultScreen(disp);  /* Obtain default screen */
    cmap = DefaultColormap(disp,scr);

    /*
     * Obtain color information :
     */
    XAllocNamedColor(disp,cmap,"red",&exact,&approx);
    red = approx.pixel;

    XAllocNamedColor(disp,cmap,"green",&exact,&approx);
    green = approx.pixel;

    XAllocNamedColor(disp,cmap,"blue",&exact,&approx);
    blue = approx.pixel;

    /*
     * Get black and white pixel values :
     */
    wht = WhitePixel(disp,scr); /* White pixel */
    blk = BlackPixel(disp,scr); /* Black pixel */

    /*
     * Choose colors for foreground and background :
     */
    fg = wht;                   /* use white foreground */
    bg = blk;                   /* use black background */

    /*
     * Set Hint Information for Window placement :
     */
    hint.x = 100;               /* Start x position */
    hint.y = 150;               /* Start y position */
    hint.width = 550;           /* Suggested width */
    hint.height = 400;          /* Suggested height */
    hint.flags = PPosition | PSize; /* pgm specified position, size */

    /*
     * Create a window to draw in :
     */
    xwin = XCreateSimpleWindow(
        disp,                   /* Display to use */
        DefaultRootWindow(disp),/* Parent window */
        hint.x, hint.y,         /* Start position */
        hint.width, hint.height,/* Window Size */
        7,                      /* Border width */
        fg,                     /* Foreground color */
        bg);                    /* Background color */

    /*
     * Specify the window and icon names :
     */
    XSetStandardProperties(
        disp,                   /* X Server connection */
        xwin,                   /* Window */
        "xegwin",               /* Window name */
        "xeg.c",                /* icon name */
        None,                   /* pixmap for icon */
        argv,argc,              /* argument values */
        &hint);                 /* sizing hints */

    /*
     * Map the window, and insure it is the topmost
     * window :
     */
    XMapRaised(disp,xwin);

    /*
     * Process the event loop :
     */
    event_loop();

    /*
     * Cleanup :
     */
    XDestroyWindow(disp,xwin);          /* Release and destroy window */
    XCloseDisplay(disp);                /* Close connection to X Server */

    return 0;
}
