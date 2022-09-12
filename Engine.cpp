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

	running = true;

}

Engine::~Engine() {
	
	for (int i = 0; i < 1000; i++)
		if(pixel_matrix[i] != nullptr)
			delete(pixel_matrix[i]);

	delete(julia);
	delete(screen);
	delete(pixel_matrix);
}

void Engine::events() {

	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {



	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}

	if (continuous_rendering) {
		screen->draw(1000, julia->julia_set(1, 1000, 2000, 0, 1000));
	}
	

}