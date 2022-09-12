#pragma once
#include "SDL.h"
#include "Window.h"
#include "Julia.h"
#include "Mandelbrot.h"


class Engine {
public:
	Engine(int width, int height);
	~Engine();
	bool running;
	void events();

private:
	double mouse_x = 0;
	double mouse_y = 0;

	bool continuous_rendering = false;
	Window* screen;
	Julia* julia;
	Mandelbrot* mandelbrot;
	int** pixel_matrix;
};

