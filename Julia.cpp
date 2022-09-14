#include "Julia.h"

void julia_set_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity, double const_x, double const_y);

Julia::Julia(int** matrix, int x_start, int x_stop, int y_start, int y_stop)
	: Drawable(x_start, x_stop, y_start, y_stop, matrix),
	Positionable(0, 0, x_stop - x_start, y_stop - y_start) {

	iterations = 128;
	infinity = 16;
	threads = 1;
	thread_pattern();
	clock = std::chrono::system_clock::now();
}

int Julia::julia_set(int type) {

	std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = point - clock;

	switch (type) {
	case 1:
		const_x = 0.7885 * cos(duration.count() / 20);
		const_y = 0.7885 * sin(duration.count() / 20);
		
		julia_set_MC();
		break;

	default:
		julia_set_MC();
		break;
	}

	return iterations;
}

void Julia::set_new_time() {
	clock = std::chrono::system_clock::now();
}

void Julia::zoom(long double times) {
	x_distance /= times;
	y_distance /= times;
	x_pixel_scale = x_distance / (double)fractal_space_x;
	y_pixel_scale = y_distance / (double)fractal_space_y;
	x_min = x_coord - (double)fractal_space_x / 2 * x_pixel_scale;
	y_min = y_coord - (double)fractal_space_y / 2 * y_pixel_scale;
}

void Julia::shift_to_mouse(long double times, int x, int y) {
	x_coord += (x - start_x - width / 2) * x_pixel_scale * times;
	y_coord += (y - start_y - height / 2) * y_pixel_scale * times;
}

void Julia::add_threads(int n) {
	if (threads + n <= MAX_THREADS && threads + n >= 1)
		threads += n;

	thread_pattern();
}

void Julia::thread_pattern() {

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

int Julia::get_threads(int i) {
	if (i == 0) {
		return th_x;
	}
	else {
		return th_y;
	}

}

int Julia::get_wanted_threads() {
	return threads;
}

void Julia::julia_set_MC() {
	int i = 0;
	for (int x = 0; x < th_x; x++) {
		for (int y = 0; y < th_y; y++) {
			thread_arr[i] = new std::thread(julia_set_SC, this, x * fractal_space_x / th_x, y * fractal_space_y / th_y, this->start_x + x * this->width / th_x, this->start_x + (x + 1) * this->width / th_x,
				this->start_y + y * this->height / th_y, this->start_y + (y + 1) * this->height / th_y, pixel_matrix, iterations, infinity, const_x, const_y);
			i++;
		}
	}

	for (int x = 0; x < i; x++) {
		thread_arr[x]->join();
		delete(thread_arr[x]);
	}
}

void julia_set_SC(Positionable* pos, int x_x, int y_y, int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix, int iterations, int infinity, double const_x, double const_y) {
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