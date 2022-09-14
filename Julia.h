#pragma once
#include "chrono"
#include "tgmath.h"
#include "thread"
#include "iostream"
#include "iostream"
#include "Positionable.h"

# define MAX_THREADS	25


class Julia : public Drawable, public Positionable {

public:

	Julia(int** matrix, int x_start, int x_stop, int y_start, int y_stop);
	int julia_set(int type);
	int infinity;
	int iterations;

	void set_new_time();
	void zoom(long double times);
	void shift_to_mouse(long double times, int x, int y);
	void add_threads(int n);
	int get_threads(int i);
	int get_wanted_threads();
	
	double const_x = 0;
	double const_y = 0;

private:
	int threads;
	int current_ths = 1;
	int th_x = 1;
	int th_y = 1;
	void julia_set_MC();
	void thread_pattern();
	std::thread* thread_arr[MAX_THREADS];
	std::chrono::system_clock::time_point clock;
};

