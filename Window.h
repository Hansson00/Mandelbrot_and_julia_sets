#pragma once
#include "SDL.h"
#include "Mandelbrot.h"
#include "iostream"
#include "Julia.h"
#include "SDL_Text.h"
#include "string"
#include "chrono"




class Window
{
public:
	
	int window_width, window_height;
	bool running = true;

	Window(int window_widthm, int window_height);
	
	void draw();
	void clean_up();

private:


	int** pixel_matrix;
	SDL_Window* window;
	SDL_Renderer* renderer;
	Julia* julia;
	SDL_Text* text;
	std::chrono::system_clock::time_point last_time;

	std::thread* threads[25];		//25 ?

	void display_fps(int x, int y);

	bool init_window(int width, int height);
	
	void draw_from_matrix(int iterations);
};

