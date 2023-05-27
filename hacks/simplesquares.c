#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<X11/Xlib.h>

// #include "vroot.h"

int main ()
{
  Display *dpy;
  Window root;
  GC g;
  Screen s;
  int snum, width, height;


  /* open the display (connect to the X server)
   * setup default screen and the dimensions
   */
  dpy = XOpenDisplay (getenv ("DISPLAY"));
  snum = DefaultScreen(dpy);
  width = DisplayWidth (dpy, snum);
  height = DisplayHeight (dpy, snum);

  printf("Default screen num: %d\n", snum);
  printf("Dimensions: %d x %d\n", width, height);

  /* get the root window */
  root = DefaultRootWindow (dpy);

  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);

  /* set foreground color */
  // XSetForeground (dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );
  XSetForeground (dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );


  /* draw something */
  while (1)
  {
    /* draw a little square */
    XFillRectangle (dpy, root, g, random()%width, random()%height, 10, 10);

    /* draw a polygon */




    /* once in a while, clear all */
    if( random()%500<1 )
      XClearWindow(dpy, root);


    /* flush changes and sleep */
    XFlush(dpy);
    usleep (10000);
  }


  XCloseDisplay (dpy);
}
