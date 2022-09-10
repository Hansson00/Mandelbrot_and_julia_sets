#include "Julia.h"

void julia_set_SC(int start_x, int stop_x, long double x_min, long double pixel_scale_x, int start_y, int stop_y, long double y_min, long double pixel_scale_y, int iterations, int infinity, int** draw_matrix, double x_const, double y_const);

Julia::Julia(int** matrix)
{
	x_min = -1.5;
	y_min = -1.5;

	x_distance = 3;
	y_distance = 3;

	x_pixel_scale = x_distance / 1000; // should be /window size
	y_pixel_scale = y_distance / 1000;

	iterations = 100;
	infinity = 16;

	pixel_matrix = matrix;

	clock = std::chrono::system_clock::now();
}

int Julia::julia_set(int type, int start_x, int stop_x, int start_y, int stop_y) {

	std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = point - clock;

	double constant = 0.7885;

	long double x_const = constant * cos(duration.count() / 10);
	long double y_const = constant * sin(duration.count() / 10);

	switch (type)
	{
	case 0:
		julia_set_SC(start_x, stop_x, x_min, x_pixel_scale, start_y, stop_y, y_min, y_pixel_scale, iterations, infinity, pixel_matrix, x_const, y_const);
		break;

	case 1:
		julia_set_MC(start_x, stop_x, start_y, stop_y, x_const, y_const);
		break;
	default:
		break;
	}

	return iterations;
}

// TODO: make a struct for all the variables
void julia_set_SC(int start_x, int stop_x, long double x_min, long double pixel_scale_x, int start_y, int stop_y, long double y_min, long double pixel_scale_y, int iterations, int infinity, int** draw_matrix, double x_const, double y_const) {
	
	long double xx = x_min + start_x * pixel_scale_x;
	long double yy;
	long double a, b, twoab, aa, bb;

	for (int x = start_x + 1; x < stop_x + 1; x++) {
		yy = y_min + start_y * pixel_scale_y;
		for (int y = start_y + 1; y < stop_y + 1; y++) {
			int n = 0;
			a = xx;
			b = yy;
			do {
				aa = a * a;
				bb = b * b;
				twoab = 2.0 * a * b;
				a = aa - bb + x_const;
				b = twoab - y_const;
				n++;
			} while (n < iterations && aa * aa + bb * bb < infinity);
			draw_matrix[x - 1][y - 1] = n;
			yy += pixel_scale_y;
		}
		xx += pixel_scale_x;
	}
}

void Julia::julia_set_MC(int start_x, int stop_x, int start_y, int stop_y, long double x_const, long double y_const) {

	for (int x = 0; x < GRID; x++) {
		for (int y = 0; y < GRID; y++) {
			threads[y * GRID + x] = new std::thread(julia_set_SC, x * (1000 / GRID), (x + 1) * 1000 / GRID, x_min, x_pixel_scale, y * (1000 / GRID), (y + 1) * 1000 / GRID, y_min, y_pixel_scale, iterations, infinity, pixel_matrix, x_const, y_const);
		}
	}

	for (int i = 0; i < GRID * GRID; i++) {
		threads[i]->join();
		delete(threads[i]);
	}
}
