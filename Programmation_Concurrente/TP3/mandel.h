/********************************************************************
 * Copyright (C) 2018                                               *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

#ifndef MANDEL_H
#define MANDEL_H

/* Command-line arguments */
extern bool auto_resize;
extern bool auto_loop;
extern bool use_threads;
extern int verbose;
extern int number_of_slices;
extern int number_of_threads;
extern int slow;

// Compute a rectangle on screen, beloning to slice number
// "slice_number" and starting at y=y_start.
void compute_rect(int slice_number, int y_start, bool &warning_emitted);

// Draw a rectangle on screen. The rectangle must previously have been
// computed by compute_rect. This version is not thread-safe:
// concurrent calls may lead to errors.
void draw_rect(int slice_number, int y_start);

// Draw a rectangle on screen. The rectangle must previously have been
// computed by compute_rect. This version is thread-safe: concurrent
// calls are possible.
void draw_rect_thread_safe(int slice_number, int y_start);

/* hardcoded parameters */
static const int rect_height = 10;

#endif // MANDEL_H
