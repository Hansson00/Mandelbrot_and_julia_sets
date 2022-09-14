#pragma once
#include "tgmath.h"
#include "thread"
#include "iostream"
#include "Positionable.h"

# define MAX_THREADS	25


class Mandelbrot : public Drawable , public Positionable {

public:

	Mandelbrot(int** matrix, int x_start, int x_stop, int y_start, int y_stop);
	int mandelbrot_set(int type);
	int infinity;
	int iterations;
	

	void zoom(long double times);
	void shift_to_mouse(long double times, int x, int y);
	void add_threads(int n);
	int get_threads(int i);
	int get_wanted_threads();

private:
	int threads;
	int current_ths = 1;
	int th_x = 1;
	int th_y = 1;
	void mandelbrot_set_MC();
	void thread_pattern();
	std::thread* thread_arr[MAX_THREADS];
};

