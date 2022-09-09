#pragma once
#include "SDL.h"
#include "Mandelbrot.h"
#include "iostream"

class Window
{
public:
	
	int window_width, window_height;
	bool running = true;
	//init
	Window(int window_widthm, int window_height);
	void clean_up();

private:
	int** pixel_matrix;
	SDL_Window* window;
	SDL_Renderer* renderer;


	bool init_window(int width, int height);


	
	
};

