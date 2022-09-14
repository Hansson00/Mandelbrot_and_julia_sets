#pragma once
#include "SDL.h"
#include "Window.h"
#include "Julia.h"
#include "Mandelbrot.h"


class Engine {
public:
	Engine(int width, int height, int fractals);
	~Engine();
	bool running;
	void events();

private:
	double mouse_x_coord = 0;
	double mouse_y_coord = 0;

	bool continuous_rendering = false;
	Window* screen;
	Julia* julia;
	Mandelbrot* mandelbrot;
	Mandelbrot* mandelbrot1;
	int** pixel_matrix;
};

