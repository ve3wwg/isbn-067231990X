/* events.c */

#include "xeg.h"

/*
 * The X Window Event Loop :
 */
void
event_loop(void) {
    int x0, y0;             /* Prior position */
    GC gc;                  /* Graphics context */
    XEvent evt;             /* X Event */
    char kbuf[8];           /* Key conv buffer */
    KeySym key;             /* Key symbol */
    int kcount;             /* Key count */
    int b = 0;              /* Buttons Pressed */
    int star = False;       /* Draw stars when True */
    Bool quit = False;      /* Quit event loop when True */

    /*
     * Choose the XEvents that we want to process :
     */
    XSelectInput(disp,xwin,
        KeyPressMask | ExposureMask |
        ButtonPressMask | ButtonReleaseMask |
        Button1MotionMask | Button2MotionMask | Button3MotionMask);

    /*
     * Create a Graphics Context :
     */
    gc = XCreateGC(disp,xwin,0,0);
    XSetBackground(disp,gc,bg); /* Set background color of gc */
    XSetForeground(disp,gc,fg); /* Set foreground color of gc */

    /*
     * Process X Events :
     */
    while ( quit != True ) {
        /*
         * Fetch an X Event :
         */
        XNextEvent(disp,&evt);

        /*
         * Process the X Event :
         */
        switch ( evt.type ) {

        case Expose :
            /*
             * Window has been exposed :
             */
            if ( evt.xexpose.count == 0 )
                XDrawImageString(evt.xexpose.display,
                    evt.xexpose.window,
                    gc,
                    105, 65,
                    "xeg.c", 5);
            break;

        case ButtonPress :
            /*
             * A button has been pressed:
             *
             * Set the bit corresponding to the moust button that
             * is pressed :
             */
            switch ( evt.xbutton.button ) {
            case Button1 :
                b |= B1;
                break;
            case Button2 :
                b |= B2;
                break;
            default :
                b |= B3;
            }

            if ( evt.xbutton.state & ShiftMask )
                star = True;
            else
                star = False;

            /*
             * Save the current position :
             */
            x0 = evt.xbutton.x;
            y0 = evt.xbutton.y;

            /*
             * Establish the drawing color based upon the leftmost
             * mouse button that is pressed :
             */
            if ( b & B1 )
                fg = red;
            else if ( b & B2 )
                fg = green;
            else
                fg = blue;

            XSetForeground(disp,gc,fg); /* Set foreground color of gc */
            break;

        case ButtonRelease :
            /*
             * A button has been released :
             *
             * Unset the bit corresponding to the released color :
             */
            switch ( evt.xbutton.button ) {
            case Button1 :
                b &= ~B1;
                break;
            case Button2 :
                b &= ~B2;
                break;
            default :
                b &= ~B3;
            }

            /*
             * Set the color based upon the leftmost mouse button :
             */
            if ( b & B1 )
                fg = red;
            else if ( b & B2 )
                fg = green;
            else
                fg = blue;
            XSetForeground(disp,gc,fg); /* Set foreground color of gc */
            break;

        case MotionNotify :
            /*
             * Motion with a button down :
             *
             * Draw a line from the last know position, to the current :
             */
            XDrawLine(disp,xwin,gc,x0,y0,evt.xmotion.x,evt.xmotion.y);

            /*
             * When drawing lines, we must save the last position that
             * we have drawn a line segment to :
             */
            if ( star == False ) {
                x0 = evt.xmotion.x;     /* Save x for next line segment */
                y0 = evt.xmotion.y;     /* Save y for next line segment */
            }
            break;

        case MappingNotify :
            XRefreshKeyboardMapping(&evt.xmapping);
            break;

        case KeyPress :
            /*
             * A key was pressed; check for 'q' to quit :
             */
            kcount = XLookupString(&evt.xkey,kbuf,sizeof kbuf,&key,0);
            if ( kcount == 1 && kbuf[0] == 'q' )
                quit = True;
        }
    }

    XFreeGC(disp,gc);                   /* Release graphics context */
}
