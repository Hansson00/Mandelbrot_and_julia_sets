#include "Engine.h"


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


	switch (fractals)
	{
	case 0:
		mandelbrot = new Fractal("Mandelbrot", pixel_matrix, 0, width, 0, window_height - STATS_HEIGHT, -0.5);
		screen->draw(mandelbrot->run_fractal(), mandelbrot);
		break;
	case 1:
		julia = new Fractal("Julia", pixel_matrix, 0, width, 0, window_height - STATS_HEIGHT, 0);
		screen->draw(julia->run_fractal(), julia);
		break;
	
	default:
		mandelbrot = new Fractal("Mandelbrot", pixel_matrix, 0, width / 2, 0, window_height - STATS_HEIGHT, -0.5);
		julia = new Fractal("Julia", pixel_matrix, width / 2, width, 0, window_height - STATS_HEIGHT, 0);
		screen->draw(mandelbrot->run_fractal(), mandelbrot);
		screen->draw(julia->run_fractal(), julia);
		break;
	}
	
	clock = std::chrono::system_clock::now();

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
		continuous_rendering = false;
		if (mandelbrot != nullptr) {
			mouse_x_coord = mandelbrot->x_coord + mandelbrot->x_pixel_scale * (mouse_x + mandelbrot->Drawable::start_x - mandelbrot->Drawable::width / 2);
			mouse_y_coord = mandelbrot->y_coord + mandelbrot->y_pixel_scale * (mouse_y - mandelbrot->Drawable::height / 2);
		}
		else {
			mouse_x_coord = julia->x_coord + julia->x_pixel_scale * (mouse_x + julia->Drawable::start_x - julia->Drawable::width / 2);
			mouse_y_coord = julia->y_coord + julia->y_pixel_scale * (mouse_y - julia->Drawable::height / 2);
		}
		
		if (julia != nullptr) {
			julia->julia_const_x = mouse_x_coord;
			julia->julia_const_y = mouse_y_coord;
			screen->draw(julia->run_fractal(), julia);
		} 
	}
	
	switch (event.type) {

	case SDL_KEYDOWN:

		switch (event.key.keysym.sym) {

		case SDLK_LSHIFT:	// Zoom in
			continuous_rendering = false;
			if (mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y)) {
				mandelbrot->shift_to_mouse(0.5, mouse_x, mouse_y);
				mandelbrot->zoom(1.25);
				screen->draw(mandelbrot->run_fractal(), mandelbrot);
			}
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y)) {
				julia->shift_to_mouse(0.5, mouse_x, mouse_y);
				julia->zoom(1.25);
				screen->draw(julia->run_fractal(), julia);
			}
			break;

		case SDLK_LCTRL:	// Zoom out
			continuous_rendering = false;
			if (mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y)) {
				mandelbrot->zoom(0.75);
				screen->draw(mandelbrot->run_fractal(), mandelbrot);
			}
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y)) {
				julia->zoom(0.75);
				screen->draw(julia->run_fractal(), julia);
			}
			break;

		case SDLK_PLUS:
			continuous_rendering = false;

			if (mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y)) {
				mandelbrot->iterations *= 2;
				screen->draw(mandelbrot->run_fractal(), mandelbrot);
			}
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y)){
				julia->iterations *= 2;
				screen->draw(julia->run_fractal(), julia);
			}
			
			break;

		case SDLK_MINUS:
			continuous_rendering = false;
			if (mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y))
				if (mandelbrot->iterations > 1) {
					mandelbrot->iterations /= 2;
					screen->draw(mandelbrot->run_fractal(), mandelbrot);
				}
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y))
				if (julia->iterations > 1) {
					julia->iterations /= 2;
					screen->draw(julia->run_fractal(), julia);
				}

			break;
		case SDLK_PAGEUP:
			if (mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y))
				mandelbrot->add_threads(1);
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y))
				julia->add_threads(1);
			break;

		case SDLK_PAGEDOWN:
			if(mandelbrot != nullptr && mandelbrot->hitbox(mouse_x, mouse_y))
				mandelbrot->add_threads(-1);
			if (julia != nullptr && julia->hitbox(mouse_x, mouse_y))
				julia->add_threads(-1);
			break;

		case SDLK_7:
			show_julia = false;
			break;

		case SDLK_8:
			continuous_rendering = false;
			show_julia = true;
			clock = std::chrono::system_clock::now();
			break;

		case SDLK_9:		// Stop rendering continuous
			continuous_rendering = false;
			break;

		case SDLK_0:		// Render continuous
			show_julia = false;
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


	if (continuous_rendering && running) {

		if(mandelbrot != nullptr)
			screen->draw(mandelbrot->run_fractal(), mandelbrot);
		if (julia != nullptr)
			screen->draw(julia->run_fractal(), julia);

	}

	if (show_julia && running) {
		if (julia != nullptr) {
			std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
			std::chrono::duration<float> duration = point - clock;
			julia->julia_const_x = 0.7885 * cos(duration.count() / 20);
			julia->julia_const_y = 0.7885 * sin(duration.count() / 20);
			screen->draw(julia->run_fractal(), julia);
		}
	}
	
	screen->display_stats(mandelbrot, julia);

}

void Engine::set_new_time() {
	clock = std::chrono::system_clock::now();
}
