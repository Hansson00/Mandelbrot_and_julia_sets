#include "Engine.h"
#

#define MAX_WIDTH 2560
#define MAX_HEIGHT 1440

Engine::Engine(int width, int height, int fractals) {

	int window_width, window_height;

	if (width > MAX_WIDTH) window_width = MAX_WIDTH;	// Init window width
	else window_width = width;

	if (height > MAX_HEIGHT) window_height = MAX_HEIGHT;// Init window height
	else window_height = height;

		pixel_matrix = new int* [MAX_WIDTH];				// Creates a matrix for all pixels
	for (int i = 0; i < MAX_WIDTH; i++) {
		pixel_matrix[i] = new int[MAX_HEIGHT];
		for (int j = 0; j < MAX_HEIGHT; j++) {
			pixel_matrix[i][j] = 0;
		}
	}

	screen = new Window(window_width, window_height, pixel_matrix, 10);

	//mandelbrot = new Mandelbrot(pixel_matrix, 500, 1500, 0, window_height);
	//screen->draw(mandelbrot->mandelbrot_set(1), mandelbrot);

	julia = new Julia(pixel_matrix, 0, window_width, 0, window_height);
	screen->draw(julia->julia_set(8), julia);
	running = true;

}

Engine::~Engine() {
	
	for (int i = 0; i < 1000; i++)
		if(pixel_matrix[i] != nullptr)
			delete(pixel_matrix[i]);

	delete(julia);
	delete(mandelbrot);
	delete(screen);
	delete(pixel_matrix);
}

void Engine::events() {

	SDL_Event event;
	SDL_PollEvent(&event);
	
	
	int mouse_x, mouse_y;
	if (SDL_GetMouseState(&mouse_x, &mouse_y) & SDL_BUTTON_LEFT != 0) { //Checks if left mb is pressed
		//continuous_rendering = false;
		std::cout << "mouse: " << mouse_x << ", " << mouse_y << std::endl;
		//mouse_x_coord = mandelbrot->x_coord + mandelbrot->x_pixel_scale * (mouse_x - 500);
		//mouse_y_coord = mandelbrot->y_coord + mandelbrot->y_pixel_scale * (mouse_y - 500);
		//screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
	}
	
	switch (event.type) {

	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {

		case SDLK_LSHIFT:	// Zoom in
			continuous_rendering = false;
			mandelbrot->shift_to_mouse(0.5, mouse_x, mouse_y);
			mandelbrot->zoom(1.25);
			screen->draw(mandelbrot->mandelbrot_set(0), mandelbrot);
			
			/*else {
				julia->shift_to_mouse(0.5, mouse_x - screen->window_width / 2, mouse_y);
				julia->zoom(1.25);
				//if (!continuous_rendering) screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
			}*/
			break;

		case SDLK_LCTRL:	// Zoom out
			continuous_rendering = false;
			mandelbrot->zoom(0.75);
			screen->draw(mandelbrot->mandelbrot_set(0), mandelbrot);
			
			/*else {
				julia->zoom(0.75);
				//if (!continuous_rendering) screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
			}*/
			break;

		case SDLK_PLUS:
			continuous_rendering = false;
			mandelbrot->iterations *= 2;
			screen->draw(mandelbrot->mandelbrot_set(0), mandelbrot);
			
			break;

		case SDLK_MINUS:
			continuous_rendering = false;
			if (mandelbrot->iterations > 1) {
				mandelbrot->iterations /= 2;
				screen->draw(mandelbrot->mandelbrot_set(0), mandelbrot);
			}
		case SDLK_PAGEUP:
			//mandelbrot->add_threads(1);
			julia->add_threads(1);
			break;

		case SDLK_PAGEDOWN:
			//mandelbrot->add_threads(-1);
			julia->add_threads(-1);
			break;

		case SDLK_9:		// Stop rendering continuous
			continuous_rendering = false;
			break;

		case SDLK_0:		// Render continuous
			continuous_rendering = true;
			break;
		default:
			break;
		}
		break;

		case SDL_QUIT:
			running = false;
			break;
		default:
			break;
	}


	if (continuous_rendering) {
		screen->draw(julia->julia_set(1), julia);
		//mandelbrot->mandelbrot_set(0);
	}
	
	screen->display_stats(nullptr, julia);

}