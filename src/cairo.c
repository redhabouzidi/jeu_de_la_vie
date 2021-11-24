#include <stdio.h>
#include <stdlib.h>
#include </usr/include/cairo/cairo.h>
#include </usr/include/cairo/cairo-xlib.h>
#include <X11/Xlib.h>

#define SIZEX 1920
#define SIZEY 1024
cairo_surface_t *cs;
void paint()
{	int i,j;
	// create cairo mask
	cairo_t *cr;
	cr=cairo_create(cs);

	// background
	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
	cairo_paint(cr);
	
	// filled rectangle
	for(i=0;i<10;i++){
	for(j=0;j<10;j++){
	cairo_rectangle(cr,(10+60*i),(10+60*j),50,50);
	cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
	cairo_fill(cr);	
	
	
	}
	}
	cairo_destroy(cr); // destroy cairo mask
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
	XSelectInput(dpy, win, KeyPressMask|KeyReleaseMask|ExposureMask|ButtonPressMask);
	XMapWindow(dpy, win);
	
	// create cairo surface
	cs=cairo_xlib_surface_create(dpy, win, DefaultVisual(dpy, 0), SIZEX, SIZEY);

	// run the event loop
	while(1) {
		XNextEvent(dpy, &e);
		if(e.type==Expose && e.xexpose.count<1) {
			paint(cs);
		} else if(e.type ==KeyPress||e.type==ButtonPress) {
		printf("%d\n",e.xkey.keycode);
		break;
		}
	}

	cairo_surface_destroy(cs); // destroy cairo surface
	XCloseDisplay(dpy); // close the display
	return 0;
}
