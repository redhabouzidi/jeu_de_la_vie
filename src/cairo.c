#include <stdio.h>
#include <stdlib.h>
#include </usr/include/cairo/cairo.h>
#include </usr/include/cairo/cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZEX 6000
#define SIZEY 10000

int a=100;
void paint(cairo_surface_t *surface)
{
	int i=0,j=0,l=10,c=10;
	// create cairo mask
	cairo_t *dr[l][c];
	dr[i][j]=cairo_create(surface);
	
	// background
	cairo_set_source_rgb (dr[i][j], 0.0, 0.0, 0.0);
	cairo_paint(dr[i][j]);
	
	// line
	
	
	

	// filled rectangle // destroy cairo mask
	for(i=0;i<l;i++){
	for(j=0;j<c;j++){
	dr[i][j]=cairo_create(surface);
	cairo_rectangle(dr[i][j],(10+60*i),(10+60*j),50,50);
	cairo_set_source_rgb (dr[i][j], 1, 0, 1);
	cairo_fill(dr[i][j]);	
	cairo_destroy(dr[i][j]);
	
	}
	}
	
	
}



int main (int argc, char *argv[]){
	// X11 display
	Display *dpy;
	Window rootwin;
	Window win;
	XEvent e;
	int scr;
	
	// init the display
	if(!(dpy=XOpenDisplay(NULL))) {
		fprintf(stderr, "ERROR: Could not open display\n");
		exit(1);
	}

	scr=DefaultScreen(dpy);
	rootwin=RootWindow(dpy, scr);

	win=XCreateSimpleWindow(dpy, rootwin, 1, 1, SIZEX, SIZEY, 0, 
			BlackPixel(dpy, scr), BlackPixel(dpy, scr));

	XStoreName(dpy, win, "jeu de la vie");
	XSelectInput(dpy, win, ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cairo_surface_t *cs; 
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs);
		} else if(e.type==ButtonPress) break;
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}

