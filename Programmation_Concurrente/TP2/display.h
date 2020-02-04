/********************************************************************
 * Copyright (C) 2018                                               *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

void init_x();

void draw_screen();

void clear_screen();

void coordinate_to_long_double(int x, int y, long double * xf, long double * yf);

void resize_according_to_mouse();

void put_pixel(int x, int y, unsigned long pixel);
unsigned long get_pixel(int x, int y);

static const unsigned long INITIAL_COLOR = 0x606060;

extern long double x_min;
extern long double x_max;
extern long double y_min;
extern long double y_max;

/* hardcoded parameters */
const int width       = 900;
const int height      = 700;

void put_image(int src_x, int src_y, int dest_x, int dest_y, unsigned int width, unsigned int height);

#endif // DISPLAY_H
