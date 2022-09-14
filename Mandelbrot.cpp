#include "Mandelbrot.h"


//void mandelbrot_set_SC(int start_x, int stop_x, long double x_coord, long double pixel_scale_x, int start_y, int stop_y, long double y_coord, long double pixel_scale_y, int iterations, int infinity, int** draw_matrix);

void mandelbrot_set_SC_new1(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity);

void mandelbrot_set_SC_new(Positionable* pos, Drawable* window, int iterations, int infinity);

Mandelbrot::Mandelbrot(int** matrix, int x_start, int x_stop, int y_start, int y_stop)
	: Drawable(x_start, x_stop, y_start, y_stop, matrix),
	  Positionable(-0.5, 0, x_stop-x_start, y_stop-y_start) {

	iterations = 64;
	infinity = 32;
	threads = 1;
	thread_pattern();
}

int Mandelbrot::mandelbrot_set(int type) {

	switch (type) {

	default:
		mandelbrot_set_MC();
		break;
	}

	return iterations;
}

void Mandelbrot::zoom(long double times) {
	x_distance /= times;
	y_distance /= times;
	x_pixel_scale = x_distance / fractal_space_x;
	y_pixel_scale = y_distance / fractal_space_y;
	x_min = x_coord - fractal_space_x / 2 * x_pixel_scale;
	y_min = y_coord - fractal_space_y / 2 * y_pixel_scale;
}

void Mandelbrot::shift_to_mouse(long double times, int x, int y) {
	
	x_coord += (x - start_x -  width/2) * x_pixel_scale * times;
	y_coord += (y - start_y - height/2) * y_pixel_scale * times;

}

void Mandelbrot::add_threads(int n){
	if (threads + n <= MAX_THREADS && threads + n >= 1) 
		threads += n;
	
	thread_pattern();
}


void Mandelbrot::thread_pattern() {

	int max = 1;
	th_x = 1;
	th_y = 1;

	for (int i = 1; i <= std::min((int)(sqrt(MAX_THREADS)), threads); i++) {
		for (int j = 1; j <= i; j++) {
			if (i * j <= MAX_THREADS && i * j > max && i * j <= threads) {
				if (this->width % i == 0 && this->height % j == 0) {
					max = i * j;
					th_x = i;
					th_y = j;
				}
			}		
		}
	}
	current_ths = max;
}

int Mandelbrot::get_threads(int i) {
	if (i == 0) {
		return th_x;
	}
	else {
		return th_y;
	}
	
}

int Mandelbrot::get_wanted_threads() {
	return threads;
}

void Mandelbrot::mandelbrot_set_MC() {
	int i = 0;
	for (int x = 0; x < th_x; x++) {
		for (int y = 0; y < th_y; y++) {
			thread_arr[i] = new std::thread(mandelbrot_set_SC_new1, this, x * fractal_space_x / th_x, y * fractal_space_y / th_y, this->start_x + x * this->width / th_x, this->start_x + (x + 1) * this->width / th_x,
				this->start_y + y * this->height / th_y, this->start_y + (y + 1) * this->height / th_y, pixel_matrix, iterations, infinity);
			i++;
		}
	}

	for (int x = 0; x < i; x++) {

		thread_arr[x]->join();
		delete(thread_arr[x]);

	}
}

void mandelbrot_set_SC_new(Positionable* pos, Drawable* window, int iterations, int infinity) {

	double xx = pos->x_min + window->start_x * pos->x_pixel_scale;
	double yy;
	double a, b, twoab, aa, bb;
	int n;

	for (int x = window->start_x; x < window->stop_x; x++) {
		yy = pos->y_min + window->start_y * pos->y_pixel_scale;
		for (int y = window->start_y; y < window->stop_y; y++) {
			n = 0;
			a = xx;
			b = yy;
			do {
				aa = a * a;
				bb = b * b;
				twoab = 2.0 * a * b;
				a = aa - bb + xx;
				b = twoab + yy;
				n++;
			} while (n < iterations && aa * aa + bb * bb < infinity);
			window->pixel_matrix[x][y] = n;
			yy += pos->y_pixel_scale;
		}
		xx += pos->x_pixel_scale;
	}

}

void mandelbrot_set_SC_new1(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y,int ** pixel_matrix, int iterations, int infinity) {
	double xx = pos->x_min + x_x * pos->x_pixel_scale;
	double yy;
	double a, b, twoab, aa, bb;
	int n;

	for (int x = start_x; x < stop_x; x++) {
		yy = pos->y_min + y_y * pos->y_pixel_scale;
		for (int y = start_y; y < stop_y; y++) {
			n = 0;
			a = xx;
			b = yy;
			do {
				aa = a * a;
				bb = b * b;
				twoab = 2.0 * a * b;
				a = aa - bb + xx;
				b = twoab + yy;
				n++;
			} while (n < iterations && aa * aa + bb * bb < infinity);
			pixel_matrix[x][y] = n;
			yy += pos->y_pixel_scale;
		}
		xx += pos->x_pixel_scale;
	}

}
