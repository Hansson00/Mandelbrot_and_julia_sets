#pragma once
#include "chrono"
#include "tgmath.h"
#include "thread"
#include "iostream"
#include "Positionable.h"

#define MAX_THREADS	25

class Fractal : public Drawable, public Positionable, public Threading{

public:
	Fractal(std::string str, int** matrix, int x_start, int x_stop, int y_start, int y_stop, double x_coord);
	~Fractal();

	int infinity;
	int iterations;

	void shift_to_mouse(long double times, int x, int y);
	
	double julia_const_x = 0;
	double julia_const_y = 0;

	int run_fractal();
private:

	void julia_MC();
	void mandelbrot_MC();
	void (Fractal::* run_fractal_)(void);

};

