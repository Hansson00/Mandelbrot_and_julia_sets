#pragma once
#include "SDL.h"
#include "Window.h"
#include "Fractal.h"
#include "chrono"


class Engine {
public:
	Engine(int width, int height, int fractals);
	~Engine();
	bool running;
	void events();
	
private:


	void set_new_time();
	std::chrono::system_clock::time_point clock;

	bool show_julia = false;
	double mouse_x_coord = 0;
	double mouse_y_coord = 0;

	bool continuous_rendering = false;
	Window* screen;
	Fractal* julia = nullptr;
	Fractal* mandelbrot = nullptr;
};
 
 