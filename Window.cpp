#include "Window.h"


#define DEBUG


Window::Window(int width, int height) {

	window_width = width;
	window_height = height;

	//Creates a matrix for all pixels
	pixel_matrix = new int* [1000];
	for (int i = 0; i < 1000; i++)
		pixel_matrix[i] = new int[1000];

	julia = new Julia(pixel_matrix);

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


void Window::draw() {

	int n = julia->julia_set(1, 0, 1000, 0, 1000);
	draw_from_matrix(n);

}

void Window::draw_from_matrix(int iterations) {

	int n;

	SDL_Surface* screen;
	screen = SDL_GetWindowSurface(window);

	SDL_LockSurface(screen);
	uint8_t* pixelArray = (uint8_t*)screen->pixels;

	for (int x = 0; x < 1000; x++) {
		for (int y = 0; y < 1000; y++) {
			n = pixel_matrix[x][y];
			if (n != iterations) {
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 0] = 50;	// B
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 1] = n * 255 / iterations;	// G
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 2] = (int)sqrt(n) * 11; 	// R
			}
			else {
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 0] = 0;		// B
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 1] = 0;		// G
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 2] = 0;		// R
			}
		}
	}

	SDL_UnlockSurface(screen);
	SDL_UpdateWindowSurface(window);


}

void Window::clean_up() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
#ifdef DEBUG
	std::cout << "Program closed" << std::endl;
#endif // DEBUG
}