#pragma once
#include "tgmath.h"
#include "thread"
#include "iostream"

# define GRID	5


class Mandelbrot {

public:

	Mandelbrot(int** matrix);
	int mandelbrot_set(int type, int x_start, int x_stop);
	double x_coord, y_coord;
	double x_distance, y_distance;
	double x_pixel_scale, y_pixel_scale;
	int iterations;
	void zoom(long double times);
	void shift_to_mouse(long double times, int x, int y);

private:

	
	int infinity;
	int** pixel_matrix;
	std::thread* threads[GRID * GRID];

	void mandelbrot_set_MC(int start_x, int stop_x, int start_y, int stop_y);

};

