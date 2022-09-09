#include "Window.h"


#define DEBUG


Window::Window(int width, int height) {

	window_width = width;
	window_height = height;
		


	//Creates a matrix for all pixels
	pixel_matrix = new int* [1000];
	for (int i = 0; i < 1000; i++)
		pixel_matrix[i] = new int[1000];

	running = Window::init_window(width, height);


}

bool Window::init_window(int width, int height) {

	window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window) {
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) return true;
	}
	#ifdef DEBUG
		std::cout << "Error: could not init window or renderer..." << std::endl;
	#endif // DEBUG
	return false;
}


void Window::clean_up() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
#ifdef DEBUG
	std::cout << "Program closed" << std::endl;
#endif // DEBUG
}