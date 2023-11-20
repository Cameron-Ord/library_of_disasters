#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
void draw_window(Display *display, Window window, XEvent *event);
int main (){

	//retrieving the display struct. If null is sent as an arg, it uses the default display.
	Display *display = XOpenDisplay(NULL);
	if (display == NULL){
		fprintf(stderr, "Unable to open display. \n");
	
		return 1;
	}

	/* 
	getting the screen number with DefaultScreen by 
	passing the display struct instance as an arg to DefaultScreen.
	*/	
	int screen = DefaultScreen(display);
	//Getting root
	Window root = RootWindow(display, screen);
	//Creating the actual window
	Window window = XCreateWindow(display, root, 10, 10, 400, 300, 1,
			       CopyFromParent, InputOutput, CopyFromParent,
			       0, NULL);
	//Setting inputs to be reported to the client application
	XSelectInput(display, window, ExposureMask | KeyPressMask);
	//Makes it viewable
	XMapWindow(display, window);
	//Declaring the event struct
	XEvent event;
	while(1) {
		XNextEvent(display, &event);
		if(event.type == Expose){	
			draw_window(display, window, &event);
		}
		if(event.type == KeyPress) {
			break;
		}
	}

	XCloseDisplay(display);
	printf("Program Closed..\n");
	return 0;
}

void draw_window(Display *display, Window window, XEvent *event){

	//Getting exposed region from the event.
	XExposeEvent *exposeEvent = &(event->xexpose);
	//Obtaining drawing context.
	GC gc = XCreateGC(display, window, 0, NULL);
	//Setting the foreground, this takes the display, GC and an unsigned long 
	/*I am using the BlackPixel macro, which takes the display struct, and the
	 screen number as arguments. I use DefaultScreen to retrieve the screen
	 number, as it returns the screen number as type int.
	*/
	XSetForeground(display, gc, BlackPixel(display, DefaultScreen(display)));
	//Using the expose event region as base area to draw.
	XFillRectangle(display, window, gc, exposeEvent->x, exposeEvent->y,
	exposeEvent->width, exposeEvent->height);
	XFreeGC(display, gc);
	XFlush(display);
}






