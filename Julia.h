#pragma once
#include "chrono"
#include "tgmath.h"
#include "thread"
#include "iostream"

# define M_PI	3.14159265358979323846
# define GRID	5


class Julia
{

public:

	Julia(int** matrix);
	int julia_set(int type, int x_start, int x_stop, double y_start, double y_stop);
	void set_new_time();
	void zoom(double times);
	void shift_to_mouse(double times, int x, int y);
	int iterations;
	double x_coord, y_coord;
	double x_distance, y_distance;
	double x_pixel_scale, y_pixel_scale;
	double const_x = 0;
	double const_y = 0;

private:
	
	
	
	int infinity;
	int** pixel_matrix;
	std::thread* threads[GRID * GRID];

	std::chrono::system_clock::time_point clock;
	
	void julia_set_MC(int start_x, int stop_x, int start_y, int stop_y, double x_const, double y_const);

};

