#include "Engine.h"

Engine::Engine()
{
	Engine(500, 500);
}

Engine::Engine(uint32_t window_width, uint32_t window_height)
{
	uint32_t** matrix = new uint32_t * [window_width];
	for (uint32_t i = 0; i < window_width; i++)
		matrix[i] = new uint32_t[window_height];
	
	const RectangleD space_rect = {3.0l, 3.0l, {-2, -1.5}};
	const RectangleI matrix_rect = { window_width , window_height, {0,0}};
	fractal = new Fractal(space_rect, matrix_rect, matrix, fractals::mandelbrot_fractal);
	window  = new Window(window_width, window_height, matrix, matrix_rect);
	running = true;
}

void Engine::main_loop()
{
	uint32_t inf = 20;
	uint32_t iter = 20;

	while (window->events())
	{
		fractal->generate_fractal(inf, iter);
		window->render(iter);
	}
}
