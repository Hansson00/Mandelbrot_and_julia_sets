#pragma once
#include "SDL.h"
#include "iostream"
#include "SDL_Text.h"
#include "string"
#include "chrono"
#include "thread"




class Window {
public:
	
	int window_width;
	int window_height;
	

	Window(int window_widthm, int window_height, int** matrix, int render_threads);
	~Window();
	void draw(int start_x, int julia_iterations);
	void clean_up();

private:

	int julia_iterations;
	int render_ths;
	int** pixel_matrix;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Text* text;
	std::chrono::system_clock::time_point last_time;

	std::thread* threads[25];		//25 ?

	void display_fps(int x, int y);

	bool init_window(int width, int height);
	
	void draw_from_matrix(int iterations, int x_start);
};

