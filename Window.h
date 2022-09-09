#pragma once
#include "SDL.h"
#include "Mandelbrot.h"
#include "iostream"
#include "Julia.h"

class Window
{
public:
	
	int window_width, window_height;
	bool running = true;
	//init
	Window(int window_widthm, int window_height);
	
	void draw();
	void clean_up();

private:
	int** pixel_matrix;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Julia* julia;

	bool init_window(int width, int height);
	
	void draw_from_matrix(int iterations);
};

