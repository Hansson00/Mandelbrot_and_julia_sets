#include "Window.h"

#define DEBUG
void draw_helper(int x0, int x1, uint8_t* pixelArray, int** draw_matrix, int iterations, SDL_Surface* screen);


double cube(double x) {
	return x * x;
}

Window::Window(int width, int height) {

	window_width = width;
	window_height = height;
	last_time = std::chrono::system_clock::now();

	//Creates a matrix for all pixels
	pixel_matrix = new int* [1000];
	for (int i = 0; i < 1000; i++)
		pixel_matrix[i] = new int[1000];

	text = new SDL_Text(16);

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

	std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = point - last_time;
	last_time = point;
	int delta_time =(int) 1 / duration.count();


	std::string fps_counter = "FPS: ";

	fps_counter.append(std::to_string(delta_time));


	text->draw_text(fps_counter, window, 10, 10, 25, 25);

	SDL_UpdateWindowSurface(window);
}

#define RENDER_THs 10

void Window::draw_from_matrix(int iterations) {

	int n;

	SDL_Surface* screen;
	screen = SDL_GetWindowSurface(window);

	SDL_LockSurface(screen);
	uint8_t* pixelArray = (uint8_t*)screen->pixels;

	std::thread* threads[RENDER_THs]; // fixa

	for (int i = 0; i < RENDER_THs; i++) {
		threads[i] = new std::thread(draw_helper, i * 1000 / RENDER_THs, (i + 1) * 1000 / RENDER_THs, pixelArray, pixel_matrix, iterations, screen);
	}

	for (int i = 0; i < RENDER_THs; i++) {
		threads[i]->join();
		delete(threads[i]);
	}

	SDL_UnlockSurface(screen);
	SDL_FreeSurface(screen);

}

void draw_helper(int x0, int x1, uint8_t* pixelArray, int** draw_matrix, int iterations, SDL_Surface* screen) {

	double n;

	for (int x = x0; x < x1; x++) {
		for (int y = 0; y < 1000; y++) {
			n = draw_matrix[x][y];
			if (n != iterations) {

				n = sqrt(n);

				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 0] = cube((cos(n + 100))) * 255; // B
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 1] = cube((cos(n+ 50))) * 255;	 // G
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 2] = cube((cos(n))) * 255; 		 // R
			}
			else {
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 0] = 0;		// B
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 1] = 0;		// G
				pixelArray[y * screen->pitch + x * screen->format->BytesPerPixel + 2] = 0;		// R
			}
		}
	}
}

void Window::clean_up() {

	delete(julia);

	for (int i = 0; i < 1000; i++) {
		delete(pixel_matrix[i]);
	}
	delete(pixel_matrix);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
#ifdef DEBUG
	std::cout << "Program closed" << std::endl;
#endif // DEBUG
}