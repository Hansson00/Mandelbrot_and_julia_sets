#include "Engine.h"


#define MAX_WIDTH 2000
#define MAX_HEIGHT 1000

Engine::Engine(int width, int height) {

	int window_width, window_height;

	if (width > MAX_WIDTH) window_width = MAX_WIDTH;	// Init window width
	else window_width = width;

	if (height > MAX_HEIGHT) window_height = MAX_HEIGHT;// Init window height
	else window_height = height;

	SDL_Init(SDL_INIT_EVERYTHING);

	pixel_matrix = new int* [MAX_WIDTH];				// Creates a matrix for all pixels
	for (int i = 0; i < MAX_WIDTH; i++) {
		pixel_matrix[i] = new int[MAX_HEIGHT];
		for (int j = 0; j < MAX_HEIGHT; j++) {
			pixel_matrix[i][j] = 0;
		}
	}

	screen = new Window(window_width, window_height, pixel_matrix, 10);

	julia = new Julia(pixel_matrix);

	mandelbrot = new Mandelbrot(pixel_matrix);

	running = true;

	screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000));
	screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));


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
		continuous_rendering = false;

		mouse_x_coord = mandelbrot->x_coord + mandelbrot->x_pixel_scale * (mouse_x - 500);
		mouse_y_coord = mandelbrot->y_coord + mandelbrot->y_pixel_scale * (mouse_y - 500);
		screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
	}
	
	switch (event.type) {

	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {

		case SDLK_LSHIFT:	// Zoom in
			if (mouse_x < screen->window_width / 2) {
				mandelbrot->shift_to_mouse(0.5, mouse_x, mouse_y);
				mandelbrot->zoom(1.5);
				screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000));
			}
			else {
				julia->shift_to_mouse(0.5, mouse_x - screen->window_width / 2, mouse_y);
				julia->zoom(1.5);
				screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
			}
			break;

		case SDLK_LCTRL:	// Zoom out
			if (mouse_x < screen->window_width / 2) {
				mandelbrot->zoom(0.5);
				screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000));
			}
			else {
				julia->zoom(0.5);
				screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
			}
			break;

		case SDLK_PLUS:
			if (mouse_x < screen->window_width / 2) {
				mandelbrot->iterations *= 2;
				screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000));
			}
			else {
				julia->iterations *= 2;
				screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
			}
			break;

		case SDLK_MINUS:
			if (mouse_x < screen->window_width / 2) {
				if (mandelbrot->iterations > 1) {
					mandelbrot->iterations /= 2;
					screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000));
				}
			}
			else {
				if (julia->iterations > 1) {
					julia->iterations /= 2;
					screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x_coord, mouse_y_coord));
				}
			}
			break;

		case SDLK_9:		// Stop rendering continuous
			continuous_rendering = false;
			break;

		case SDLK_0:		// Render continuous
			continuous_rendering = true;
			julia->set_new_time();
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
		screen->draw(0, 64);
		//screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000, 0, 1000));
		//screen->draw(1000, julia->julia_set(1, 1000, 2000, 0, 0));
	}
	

}