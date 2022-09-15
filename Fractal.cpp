#include "Fractal.h"

void julia_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity, double const_x, double const_y);
void mandelbrot_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity);

Fractal::Fractal(std::string str, int** matrix, int x_start, int x_stop, int y_start, int y_stop, double x_coord) :
Drawable(x_start, x_stop, y_start, y_stop, matrix),
Positionable(x_coord, 0, x_stop - x_start, y_stop - y_start),
Threading(1, x_stop - x_start, y_stop - y_start){

	if (str._Equal("Mandelbrot")) run_fractal_ = &Fractal::mandelbrot_MC;
	else run_fractal_ = &Fractal::julia_MC;

	iterations = 128;
	infinity = 32;
}

void Fractal::shift_to_mouse(long double times, int x, int y) {
	x_coord += (x - start_x - Drawable::width / 2) * x_pixel_scale * times;
	y_coord += (y - start_y - Drawable::height / 2) * y_pixel_scale * times;
}

int Fractal::run_fractal()
{
	(this->*run_fractal_)();
	return iterations;
}

void Fractal::julia_MC() {
	int i = 0;
	for (int x = 0; x < th_x; x++) {
		for (int y = 0; y < th_y; y++) {
			thread_arr[i] = new std::thread(julia_SC, this, x * fractal_space_x / th_x, y * fractal_space_y / th_y, this->start_x + x * this->Drawable::width / th_x, this->start_x + (x + 1) * this->Drawable::width / th_x,
				this->start_y + y * this->Drawable::height / th_y, this->start_y + (y + 1) * this->Drawable::height / th_y, pixel_matrix, iterations, infinity, julia_const_x, julia_const_y);
			i++;
		}
	}
	for (int x = 0; x < i; x++) {
		thread_arr[x]->join();
		delete(thread_arr[x]);
	}
}

void julia_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity, double const_x, double const_y) {
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
				a = aa - bb + const_x;
				b = twoab + const_y;
				n++;
			} while (n < iterations && aa * aa + bb * bb < infinity);
			pixel_matrix[x][y] = n;
			yy += pos->y_pixel_scale;
		}
		xx += pos->x_pixel_scale;
	}

}

void Fractal::mandelbrot_MC() {
	int i = 0;
	for (int x = 0; x < th_x; x++) {
		for (int y = 0; y < th_y; y++) {
			thread_arr[i] = new std::thread(mandelbrot_SC, this, x * fractal_space_x / th_x, y * fractal_space_y / th_y, this->start_x + x * this->Drawable::width / th_x, this->start_x + (x + 1) * this->Drawable::width / th_x,
				this->start_y + y * this->Drawable::height / th_y, this->start_y + (y + 1) * this->Drawable::height / th_y, pixel_matrix, iterations, infinity);
			i++;
		}
	}

	for (int x = 0; x < i; x++) {

		thread_arr[x]->join();
		delete(thread_arr[x]);

	}
}

void mandelbrot_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity) {
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

