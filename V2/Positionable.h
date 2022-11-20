#pragma once
#include "thread"
#include "tgmath.h"
#include "iostream"

#define MAX_THREADS 25

class Positionable {

public:
	Positionable(double x_coord, double y_coord, double window_width, double window_height);
	~Positionable();
	double x_coord, y_coord;
	double x_min, y_min;
	double x_distance, y_distance;
	double x_pixel_scale, y_pixel_scale;
	int fractal_space_x, fractal_space_y;

	void zoom(long double times);
};

class Drawable {

public:
	Drawable(int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix);
	~Drawable();
	void set_new_window(int start_x, int stop_x, int start_y, int stop_y);
	bool hitbox(int x, int y);
	int** pixel_matrix;
	int start_x, stop_x;
	int start_y, stop_y;
	int width, height;
};

class Threading {
public:
	Threading(int threads, int width, int height);
	~Threading();
	void add_threads(int n);
	int get_threads(int i);
	int get_wanted_threads();


protected:
	void thread_pattern();
	int threads;
	int th_x = 1;
	int th_y = 1;
	std::thread* thread_arr[MAX_THREADS];

private:
	int width;
	int height;
};
