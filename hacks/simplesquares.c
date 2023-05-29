#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<X11/Xlib.h>

// #include "vroot.h"

int main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  GC g;
  int width, height;
  XPoint center;
  unsigned char R_val, G_val, B_val;
  XColor xc, sc;
  char color_str[100];


  /* open the display (connect to the X server)
   * setup default screen and the dimensions
   */
  dpy = XOpenDisplay (getenv ("DISPLAY"));

  center.x = width/2, center.y = height/2;


  /* get the root window */
  root = DefaultRootWindow (dpy);

  /* get window attributes */
  XGetWindowAttributes(dpy, root, &wa);

  /* set screen dimensions */
  width = wa.width;
  height = wa.height;
  printf("Dimensions: %d x %d\n", width, height);

  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);



  /* draw something */
  while (1)
  {
    XPoint points[4];
    short psize = 30;
    points[0].x = -psize, points[0].y = psize;
    points[1].x = psize, points[1].y = psize;
    points[2].x = psize, points[2].y = -psize;
    points[3].x = -psize, points[3].y = -psize;
    for (int i = 0; i < 4; i++) {
      points[i].x += center.x;
      points[i].y += center.y;
    }

    /* clean str buf */
    memset(color_str, sizeof(color_str), 0);

    /* assign rgb val randomly */
    R_val = random(), G_val = random(), B_val = random();

    /* set color */
    XAllocNamedColor(dpy, DefaultColormapOfScreen(DefaultScreenOfDisplay(dpy)), "RGBi:100.0/0.0/0.0", &reds, &redx);
    XSetForeground (dpy, g, sc.pixel );

    /* draw a little square */
    XFillRectangle (dpy, root, g, random()%width, random()%height, 10, 10);

    /* draw a polygon */
    // XFillPolygon (dpy, root, g, points, 4, Convex, CoordModeOrigin);

    /* draw a point */
    // XDrawPoint(dpy, root, g, random()%width, random()%height);
    
    /* draw points */

    /* once in a while, clear all */
    if( random()%500<1 )
      XClearWindow(dpy, root);


    /* flush changes and sleep */
    XFlush(dpy);
    usleep (10000);
  }


  XCloseDisplay (dpy);
}
