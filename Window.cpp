#include "Window.h"


#define MAX_WIDTH 2000
#define MAX_HEIGHT 1050
#define STATS_HEIGHT 50


#define DEBUG
void draw_helper(int x0, int x1, int y_height, uint8_t* pixelArray, int** draw_matrix, int iterations, SDL_Surface* screen);

double cube(double x) {
	return x * x;
}

Window::Window(int width, int height, int** matrix, int render_threads) {

	window_width = width;
	
	window_height = height;

	last_time = std::chrono::system_clock::now();		// FPS clock

	pixel_matrix = matrix;

	text = new SDL_Text(20);							// Init text display

	render_ths = render_threads;

	Window::init_window(window_width, window_height);		// Init window
}

Window::~Window() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

void Window::display_fps(int x, int y) {

	static int i = 0;
	static int delta_t = 0;
	static int smooth_fps = 60;

	std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = point - last_time;
	last_time = point;

	if (i > 4) {
		i = 0;
		smooth_fps = delta_t / 5;
		delta_t = 0;
	}
	delta_t += (int) 1 / duration.count();
	i++;
	std::string fps_counter = "FPS: ";
	fps_counter.append(std::to_string(smooth_fps));
	text->draw_text(fps_counter, window, x, y);
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

void Window::draw(int start_x, int iterations) {
	draw_from_matrix(iterations, start_x);					// draw
	Window::display_fps(10 + start_x, 10);									// display fps counter att 10, 10
	SDL_UpdateWindowSurface(window);								// draw call
}

void Window::draw_from_matrix(int iterations, int x_start) {

	SDL_Surface* screen = SDL_GetWindowSurface(window);

	SDL_LockSurface(screen);
	uint8_t* pixelArray = (uint8_t*)screen->pixels;

	//TODO: Make the funtion general
	for (int i = 0; i < render_ths; i++) {
		threads[i] = new std::thread(draw_helper, i * 1000 / render_ths + x_start, (i + 1) * 1000 / render_ths + x_start, window_height-STATS_HEIGHT, pixelArray, pixel_matrix, iterations, screen);
	}

	for (int i = 0; i < render_ths; i++) {
		threads[i]->join();
		delete(threads[i]);
	}
	SDL_UnlockSurface(screen);
	SDL_FreeSurface(screen);

}

void draw_helper(int x0, int x1, int y_height, uint8_t* pixelArray, int** draw_matrix, int iterations, SDL_Surface* screen) {

	double n;

	for (int x = x0; x < x1; x++) {
		for (int y = 0; y < y_height; y++) {
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