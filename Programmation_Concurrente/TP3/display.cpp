/********************************************************************
 * Copyright (C) 2018                                               *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>

#include "display.h"

long double x_min = -2;
long double x_max = 1;
long double y_min = -1.3;
long double y_max = 1.3;

Display		  *display;
Window		   window;
int		   screen;
int		   depth;
GC		   gc;
char		  *buffer;
XImage		  *image;
Colormap	   cmap;
int		   color_table[256];

void put_pixel(int x, int y, unsigned long pixel) {
	XPutPixel(image, x, y, pixel);
}

unsigned long get_pixel(int x, int y) {
	return XGetPixel(image, x, y);
}

void init_x() {
	static XSizeHints  size_hints;
	Visual		  *visual;
	Window		   rootwin;
	XGCValues	   values;
	unsigned long	   valuemask = 0;
	display = XOpenDisplay(NULL);

	if (display == NULL) {
		fprintf(stderr, "Failed to open Display!");
		exit (1);
	}

	screen	= DefaultScreen(display);
	depth	= DefaultDepth(display, screen);
	visual	= DefaultVisual(display, screen);
	cmap	= DefaultColormap(display, screen);
	rootwin = RootWindow(display, screen);
	window	= XCreateSimpleWindow(display, rootwin, 10, 10, width, height, 5,
				      BlackPixel(display, screen), BlackPixel(display, screen));

	size_hints.flags = PSize | PMinSize | PMaxSize;
	size_hints.min_width  = width;
	size_hints.max_width  = width;
	size_hints.min_height = height;
	size_hints.max_height = height;

	XSetWindowColormap(display, window, cmap);

	//	  init_colormap();

	gc = XCreateGC(display, window, valuemask, &values);

	XSetStandardProperties(display, window, "Mandelbrot", "Mandelbrot", None, 0, 0, &size_hints);

	XSelectInput(display, window, ButtonPressMask | KeyPressMask);
	XMapWindow(display, window);

	buffer = 0;
	
	image = XCreateImage(display, visual, depth, ZPixmap, 0, buffer, width, height, 8, 0);
	{
		// tricks to have it working in non 8-bit depth
		int imgsize = image->height * image->bytes_per_line;
		buffer = (char *)malloc(imgsize);
		int i;
		for (i = 0; i < imgsize; i++) buffer[i] = 0;
	}
	image->data = buffer;

	XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);
	/* Ugly workaround for a display bug. The window may not be
	   properly mapped at this point, and if it's not clear_screen()
	   won't have any effect. Wait for the window to be actually
	   displayed (and refresh to the initial color to make sure we
	   visually see INITIAL_COLOR when the window pops up).
	*/
	for (int i = 0; i < 20; i++) {
		clear_screen();
		usleep(10000);
	}
}


void draw_screen () {
	XPutImage(display, window, gc, image, 0, 0, 0, 0, width, height);

	/* Not necessary strictly speaking, but without this XSync,
	   the xlib already acts as a producer/consumer with a
	   buffer, so the effect of doing a producer/consumer
	   ourserves is not visible. */
	XSync(display, 0);
}

void clear_screen() {
	int x;
	int y;
	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
			XPutPixel(image, x, y, INITIAL_COLOR);
		}
	}
	draw_screen();
}

void coordinate_to_long_double(int x, int y, long double * xf, long double * yf) {
	*xf = (long double)x;
	*yf = (long double)y;
	*xf = (*xf / width) * (x_max - x_min) + x_min;
	*yf = (*yf / height) * (y_max - y_min) + y_min;
}

void resize_according_to_mouse () {
	Window root_return;
	Window child_return;
	int root_x_return, root_y_return, win_x_return, win_y_return;
	unsigned int mask_return;
	long double x_center, y_center;
	long double x_size, y_size;
	XQueryPointer(display, window,
		      &root_return,
		      &child_return,
		      &root_x_return,
		      &root_y_return,
		      &win_x_return,
		      &win_y_return,
		      &mask_return);
	coordinate_to_long_double(win_x_return, win_y_return,
				  &x_center, &y_center);
	x_size = x_max - x_min;
	y_size = y_max - y_min;
	x_min = x_center - (x_size / 10);
	y_min = y_center - (y_size / 10);
	x_max = x_center + (x_size / 10);
	y_max = y_center + (y_size / 10);
	printf ("x_min = %f;\ny_min = %f;\nx_max = %f;\ny_max = %f;\n",
		(float)x_min, (float)y_min, (float)x_max, (float)y_max);
}

void put_image(int src_x, int src_y, int dest_x, int dest_y, unsigned int width, unsigned int height) {
	XPutImage(display, window, gc, image,
		  src_x, src_y, dest_x, dest_y, width, height);

	/* Pas strictement nécessaire, mais si on utilise X de manière
	 * asynchrone, on ne voit pas le bénéfice d'avoir un thread
	 * séparé pour X, puisque c'est la xlib qui travaille en
	 * producteur-consommateur avec un buffer. */
	XSync(display, 0);

}
