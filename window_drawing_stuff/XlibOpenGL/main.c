#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <X11/Xutil.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void init_gl();
void handle_expose(Display *display, Window window);
void draw_cube();
int main (){
	Display *display = XOpenDisplay(NULL);
	if (display == NULL){
		fprintf(stderr, "Unable to open display. \n");
		return 1;
	}

	Window root = DefaultRootWindow(display);
	XVisualInfo *Visual_Info = glXChooseVisual(display, 0, NULL);
	XSetWindowAttributes set_win_attr;
	set_win_attr.colormap = XCreateColormap(display, root, Visual_Info->visual, AllocNone);
	set_win_attr.border_pixel = 0;
	Window window = XCreateWindow(display, root, 0, 0, 800, 600, 0 ,
			       Visual_Info->depth, InputOutput, Visual_Info->visual,
			       CWBorderPixel | CWColormap, &set_win_attr);
	XMapWindow(display, window);
	XStoreName(display, window, "Open GL Rendering");

	GLXContext glx_context = glXCreateContext(display, Visual_Info, NULL, GL_TRUE);
	GLenum error = glGetError();	
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
		return 1;
	}
	glXMakeCurrent(display,window,glx_context);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
		return 1;
	}
	glEnable(GL_DEPTH_TEST);
	error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "OpenGL error: %d\n", error);
		return 1;
	}	
	XSelectInput(display, window, ExposureMask | KeyPressMask);
	init_gl();

	XEvent event;
	while(1)
	{
		XNextEvent(display, &event);
		if(event.type == Expose){
			handle_expose(display, window);
		} else if (event.type == KeyPress) {
			break;
		}
	}

	glXDestroyContext(display, glx_context);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	return 0;
}

void init_gl(){
	glMatrixMode(GL_PROJECTION);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
	    fprintf(stderr, "OpenGL error: %d\n", error);
	}
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	error = glGetError();
	if (error != GL_NO_ERROR) {
	    fprintf(stderr, "OpenGL error: %d\n", error);
	}
	gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);
	
}

void handle_expose(Display *display, Window window){
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
	    fprintf(stderr, "OpenGL error: %d\n", error);
	}
	draw_cube();
	glXSwapBuffers(display, window);
}

void draw_cube(){
	glBegin(GL_QUADS);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
	    fprintf(stderr, "OpenGL error: %d\n", error);
	}
	glColor3f(1.0,0.0,0.0);
	glVertex3f(-1.0, -1.0, -1.0);
	glVertex3f(1.0, -1.0, -1.0);
	glVertex3f(1.0, 1.0, -1.0);
	glVertex3f(-1.0, 1.0, -1.0);
	glEnd();
}



