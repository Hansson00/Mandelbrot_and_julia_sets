#include "Engine.h"

Engine::Engine()
{
	Engine(500, 500);
}

Engine::Engine(uint32_t window_width, uint32_t window_height):
	running(true)
{
	uint32_t** matrix = new uint32_t * [window_width];
	for (uint32_t i = 0; i < window_width; i++)
		matrix[i] = new uint32_t[window_height];
	
	const RectangleD space_rect = {3.0l, 3.0l, {-1, 0}};
	const RectangleI matrix_rect = { window_width , window_height, {0,0}};
	fractal = new Fractal(space_rect, matrix_rect, matrix, fractals::mandelbrot_fractal);
	window  = new Window(window_width, window_height, matrix, matrix_rect);
}

void Engine::main_loop()
{

	uint64_t i = 0;

	double time = 0;

	while (running)
	{
		auto start = std::chrono::system_clock::now();
		
		fractal->generate_fractal(infinity, iterations);
		
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - start;
		time += diff.count();

		window->render(iterations);
		events();

		i++;
	}

	std::cout << time / i << std::endl;
}

void Engine::events()
{

	using enum Key;

	if (const auto key = window->events(); key) {
		const KeyEvent key_value = key.value();
		switch (key_value.key)
		{
		case ESC: running = false; return;
		case LSHIFT: 
			/* Zooms in on the fractal by making its window smaller. */
			fractal->space_rect /= 1.5;
			/* Moves the center of the fractal towards the mouse. */
			fractal->translate({(double)key_value.mouse_x, (double)key_value.mouse_y });
			return;
			/* Zooms out of the fractal by making its window larger. */
		case LCTRL: fractal->space_rect *= 1.5; return;

		case PGUP: iterations = iterations << 2; return;
		case PGDN: iterations = iterations == 1 ? iterations : iterations >> 2; return;


		default:
			break;
		}

	}
}