#pragma once
#include "SDL.h"
#include "iostream"
#include "SDL_Text.h"
#include "string"
#include "chrono"
#include "thread"
#include "Mandelbrot.h"
#include "Julia.h"
#include "Positionable.h"




class Window {
public:
	
	int window_width;
	int window_height;

	Window(int window_widthm, int window_height, int** matrix, int render_threads);
	~Window();
	void draw(int iterations, Drawable* win);
	void display_fps(int x, int y, SDL_Surface* s);
	void display_stats(Mandelbrot* m, Julia* j);

private:

	int julia_iterations;
	int render_ths;
	int** pixel_matrix;
	SDL_Window* window;
	SDL_Text* text;
	std::chrono::system_clock::time_point last_time;

	std::thread* threads[10];

	

	bool init_window(int width, int height);
	
	void draw_from_matrix(int iterations, Drawable* win);
};

