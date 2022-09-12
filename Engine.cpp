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

	screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000, 0, 1000));
	screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x, mouse_y));


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
	switch (event.type) {
	case SDL_MOUSEBUTTONDOWN:
		switch (event.button.button)
		{
			case SDL_BUTTON_LEFT:

				int x, y;

				SDL_GetMouseState(&x, &y);

				mouse_x = mandelbrot->x_min + x * mandelbrot->x_pixel_scale;
				mouse_y = mandelbrot->y_min + y * mandelbrot->y_pixel_scale;
				screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x, mouse_y));

				break;
		default:
			break;
		}

		//if (event.key.keysym.sym == SDLK_MINUS) {
		break;



	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}

	if (continuous_rendering) {
		screen->draw(0, mandelbrot->mandelbrot_set(1, 0, 1000, 0, 1000));
		screen->draw(1000, julia->julia_set(2, 1000, 2000, mouse_x, mouse_y));
	}
	

}