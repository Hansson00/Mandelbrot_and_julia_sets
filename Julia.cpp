#include "Julia.h"

void julia_set_SC(int start_x, int stop_x, double x_coord, double pixel_scale_x, int start_y, int stop_y, double y_coord, double pixel_scale_y, int iterations, int infinity, int** draw_matrix, double x_const, double y_const);

Julia::Julia(int** matrix)
{
	x_coord = 0;
	y_coord = 0;

	x_distance = 3;
	y_distance = 3;

	x_pixel_scale = x_distance / 1000; // should be /window size
	y_pixel_scale = y_distance / 1000;

	iterations = 128;
	infinity = 16;

	pixel_matrix = matrix;

	clock = std::chrono::system_clock::now();
}

int Julia::julia_set(int type, int start_x, int stop_x, double start_y, double stop_y) {

	std::chrono::system_clock::time_point point = std::chrono::system_clock::now();
	std::chrono::duration<float> duration = point - clock;

	double constant = 0.7885;

	double x_const = constant * cos(duration.count() / 20);
	double y_const = constant * sin(duration.count() / 20);

	switch (type)
	{
	case 0:

		const_x = x_const;
		const_y = y_const;
		julia_set_SC(start_x, stop_x, x_coord, x_pixel_scale, 0, 1000, y_coord, y_pixel_scale, iterations, infinity, pixel_matrix, x_const, y_const);
		break;

	case 1:
		const_x = x_const;
		const_y = y_const;
		julia_set_MC(start_x, stop_x, 0, 1000, x_const, y_const);
		break;

	case 2:
		const_x = start_y;
		const_y = stop_y;
		julia_set_MC(start_x, stop_x, 0, 1000, start_y, stop_y);
		break;

		break;
	default:
		break;
	}

	return iterations;
}

void Julia::set_new_time() {
	clock = std::chrono::system_clock::now();
}

void Julia::zoom(double times) {
	x_distance /= times;
	y_distance /= times;
	x_pixel_scale = x_distance / 1000;	//Window_width
	y_pixel_scale = y_distance / 1000;	//Window_width
}

void Julia::shift_to_mouse(double times, int x, int y) {
	x_coord += (x - 500) * x_pixel_scale * times;
	y_coord += (y - 500) * y_pixel_scale * times;
}

// TODO: make a struct for all the variables

void julia_set_SC(int start_x, int stop_x, double x_coord, double pixel_scale_x, int start_y, int stop_y, double y_coord, double pixel_scale_y, int iterations, int infinity, int** draw_matrix, double x_const, double y_const) {
	
	double xx = x_coord - pixel_scale_x*500 + (start_x % 1000) * pixel_scale_x;
	double yy;
	double a, b, twoab, aa, bb;

	for (int x = start_x + 1; x < stop_x + 1; x++) {
		yy = y_coord - pixel_scale_y * 500 + (start_y % 1000)* pixel_scale_y;
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

void Julia::julia_set_MC(int start_x, int stop_x, int start_y, int stop_y, double x_const, double y_const) {

	for (int x = 0; x < GRID; x++) {
		for (int y = 0; y < GRID; y++) {
			threads[y * GRID + x] = new std::thread(julia_set_SC, x * (1000 / GRID) + start_x, (x + 1) * 1000 / GRID + stop_x - start_x, x_coord, x_pixel_scale, y * (1000 / GRID), (y + 1) * 1000 / GRID, y_coord, y_pixel_scale, iterations, infinity, pixel_matrix, x_const, y_const);
		}
	}

	for (int i = 0; i < GRID * GRID; i++) {
		threads[i]->join();
		delete(threads[i]);
	}
}
