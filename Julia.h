#pragma once
#include "chrono"
#include "tgmath.h"
#include "thread"

# define M_PI	3.14159265358979323846
# define GRID	5


class Julia
{

public:
	Julia(int** matrix);
	int julia_set(int type, int x_start, int x_stop, int y_start, int y_stop);

	

private:
	
	double x_min, y_min;
	double x_distance, y_distance;
	double x_pixel_scale, y_pixel_scale;
	int iterations;
	int infinity;
	int** pixel_matrix;

	std::chrono::system_clock::time_point clock;
	
	void julia_set_MC(int start_x, int stop_x, int start_y, int stop_y, long double x_const, long double y_const);

};
