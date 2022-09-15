#include "Window.h"

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

	text = new SDL_Text(16);							// Init text display

	render_ths = render_threads;

	Window::init_window(window_width, window_height);	// Init window
}

Window::~Window() {

	SDL_DestroyWindow(window);
}

void Window::display_fps(int x, int y, SDL_Surface* s) {

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
	
	if (smooth_fps > 200) fps_counter.append("NaN");
	else fps_counter.append(std::to_string(smooth_fps));
	text->draw_text(fps_counter, s, x, y);
}

void zoom_display(double zoom, std::string * str) {

	if (zoom / 1000 > 1) {
		if (zoom / 1000000 > 1) {
			if (zoom / 1000000000 > 1) {
				str->append(std::to_string((int)( zoom / 1000000000.0f)));
				str->append("e^9");
				return;
			}
			str->append(std::to_string((int)(zoom / 1000000.0f)));
			str->append("e^6");
			return;
		}
		str->append(std::to_string((int)(zoom / 1000.0f)));
		str->append("e^3");
		return;
	}
	str->append(std::to_string((int)zoom));
	return;
}

void Window::display_stats(Fractal* m, Fractal* j) {

	SDL_Surface* poggers = SDL_CreateRGBSurface(0, window_width, 25, 32, 0, 0, 0, 0);
	Window::display_fps(5, 0, poggers);
	std::string str = "Coordinates: ";
	if (m != nullptr) {

		str.append(std::to_string((float)m->x_coord));
		str.append("x, ");
		str.append(std::to_string((float)m->y_coord));
		str.append("y  Zoom: ");
		zoom_display((3.0 / m->x_distance), &str);
		str.append("x  Iterations: ");
		str.append(std::to_string(m->iterations));
		str.append("  Threads: ");
		str.append(std::to_string(m->get_wanted_threads()));
		str.append("(");
		str.append(std::to_string(m->get_threads(0)));
		str.append("x");
		str.append(std::to_string(m->get_threads(1)));
		str.append(")");
		text->draw_text(str, poggers, 100, 0);
	}
	if (j != nullptr) {
		
		str = "Coordinates: ";
		str.append(std::to_string((float)j->x_coord));
		str.append("x, ");
		str.append(std::to_string((float)j->y_coord));
		str.append("y  Zoom: ");
		zoom_display((3.0 / j->x_distance), &str);
		str.append("  Iterations: ");
		str.append(std::to_string(j->iterations));
		str.append("  Threads: ");
		str.append(std::to_string(j->get_wanted_threads()));
		str.append("(");
		str.append(std::to_string(j->get_threads(0)));
		str.append("x");
		str.append(std::to_string(j->get_threads(1)));
		str.append(")");
		str.append("  Constant: ");
		str.append(std::to_string((float)j->julia_const_x));
		str.pop_back();
		str.pop_back();
		str.pop_back();
		str.append("x, ");
		str.append(std::to_string((float)-j->julia_const_y));
		str.pop_back();
		str.pop_back();
		str.pop_back();
		str.append("y");

		if(m != nullptr)
			text->draw_text(str, poggers, window_width / 2, 0);
		else
			text->draw_text(str, poggers, 100, 0);
	}
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	SDL_Rect rect = { 0, window_height- STATS_HEIGHT, 0, 0 };

	SDL_BlitSurface(poggers, NULL, screen, &rect);

	SDL_FreeSurface(screen);
	SDL_FreeSurface(poggers);
	SDL_UpdateWindowSurface(window);


}

bool Window::init_window(int width, int height) {

	window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
	if (window) return true;
	#ifdef DEBUG
		std::cout << "Error: could not init window or renderer..." << std::endl;
	#endif // DEBUG
	return false;
}

void Window::draw(int iterations, Drawable* win) {
	draw_from_matrix(iterations, win);					// draw
}

void Window::draw_from_matrix(int iterations, Drawable* win) {

	SDL_Surface* screen = SDL_GetWindowSurface(window);

	SDL_LockSurface(screen);
	uint8_t* pixelArray = (uint8_t*)screen->pixels;

	//TODO: Make the funtion general
	for (int i = 0; i < render_ths; i++) {
		threads[i] = new std::thread(draw_helper, i * win->width / render_ths + win->start_x, (i + 1) * win->width / render_ths + win->start_x, window_height, pixelArray, pixel_matrix, iterations, screen);
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