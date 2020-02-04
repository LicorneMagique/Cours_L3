/********************************************************************
 * Copyright (C) 2008 by Verimag and Ensimag                        *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#include "mandel.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <iostream>
#include <sstream>
#include <mutex>

#include "display.h"

/* command line options */
bool auto_resize = false;
bool auto_loop = false;
bool use_threads = false;
int verbose = 0;
int number_of_slices = 20;
int number_of_threads = 1;
int slow = 0;

//int max_iteration = INT_MAX;
int max_iteration = 5000;

int iteration_color(int iteration) {
	iteration <<= 2;
	while (1) {
		if (iteration <= 0xFF) {
			return iteration;
		}
		iteration -= 0xFF;
		if (iteration <= 0xFF) {
			return (iteration << 8) + (0xFF-iteration);
		}
		iteration -= 0xFF;
		if (iteration <= 0xFF) {
			return (iteration << 16) + ((0xFF-iteration) << 8);
		}
		iteration -= 0xFF;
		if (iteration <= 0xFF ) {
			return ((0xFF - iteration) << 16);
		}
		iteration -= 0xFF;
	}
}

unsigned long mandelbrot_pixel(int x_int, int y_int)
{
	for (volatile int i = 0; i < 10000 * slow; i++)
		continue;
	long double x0, y0, x, y;
	int iteration = 0;

	coordinate_to_long_double(x_int, y_int, &x0, &y0);
	x = x0;
	y = y0;

	while ( x*x + y*y <= 4.0  &&  iteration++ < max_iteration ) {
		if (slow)
			for (volatile int i = 0; i < 10 * slow; i++)
				continue;
		long double xtemp = x*x - y*y + x0;
		y = 2*x*y + y0;
		x = xtemp;
	}
	if ( iteration >= max_iteration ) {
		return 0;
	} else {
		//printf("iteration=%d\n", iteration);
		return iteration_color(iteration);
	}
}

void draw_rect_thread_safe(int slice_number, int y_start) {
	static std::mutex m;
	std::unique_lock<std::mutex> l(m);
	draw_rect(slice_number, y_start);
}

void draw_rect(int slice_number, int y_start) {
	// printf("Drawing rectangle %d,%d\n", slice_number, y_start);
	int x_start = (width * slice_number) / number_of_slices;
	int x_end   = (width * (slice_number + 1)) / number_of_slices;

	put_image(x_start, y_start,
		  x_start, y_start,
		  x_end - x_start, rect_height);
}

void compute_rect(int slice_number, int y_start, bool &warning_emitted) {
        for (int y = y_start; y < y_start + rect_height; y++) {
		for (int x = (width * slice_number) / number_of_slices;
		     x < (width * (slice_number + 1)) / number_of_slices;
		     x++) {
			if (get_pixel(x, y) != INITIAL_COLOR) {
				if (!warning_emitted) {
					std::ostringstream o;
					o << "Pixel already computed on slice "
					  << slice_number << " !" << std::endl;
					std::cout << o.str();
					warning_emitted = true;
				}
				// Big red warning
				put_pixel(x, y, 0xFF0000);
			} else {
				put_pixel(x, y, mandelbrot_pixel(x, y));
			}
		}
	}
}
