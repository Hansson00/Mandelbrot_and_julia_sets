#include "Mandelbrot.h"


void mandelbrot_set_SC(int start_x, int stop_x, long double x_coord, long double pixel_scale_x, int start_y, int stop_y, long double y_coord, long double pixel_scale_y, int iterations, int infinity, int** draw_matrix);

Mandelbrot::Mandelbrot(int** matrix)
{
	x_coord = -0.5;
	y_coord = 0;

	x_distance = 3;
	y_distance = 3;

	x_pixel_scale = x_distance / 1000; // should be /window size
	y_pixel_scale = y_distance / 1000;

	iterations = 64;
	infinity = 16;

	pixel_matrix = matrix;
}

int Mandelbrot::mandelbrot_set(int type, int start_x, int stop_x) {

	switch (type) {
	case 0:
		mandelbrot_set_SC(start_x, stop_x, x_coord, x_pixel_scale, 0, 1000, y_coord, y_pixel_scale, iterations, infinity, pixel_matrix);
		break;

	case 1:
		mandelbrot_set_MC(start_x, stop_x, 0, 1000);
		break;
	default:
		break;
	}

	return iterations;
}

void Mandelbrot::zoom(long double times) {
	x_distance /= times;
	y_distance /= times;
	x_pixel_scale = x_distance / 1000;	//Window_width
	y_pixel_scale = y_distance / 1000;	//Window_width
}

void Mandelbrot::shift_to_mouse(long double times, int x, int y) {
	
	x_coord += (x - 500) * x_pixel_scale * times;
	y_coord += (y - 500) * y_pixel_scale * times;

}

void mandelbrot_set_SC(int start_x, int stop_x, long double x_min, long double pixel_scale_x, int start_y, int stop_y, long double y_min, long double pixel_scale_y, int iterations, int infinity, int** draw_matrix) {

	double xx = x_min - 500* pixel_scale_x + (start_x % 1000) * pixel_scale_x;
	double yy;
	double a, b, twoab, aa, bb;

	for (int x = start_x + 1; x < stop_x + 1; x++) {
		yy = y_min - 500 * pixel_scale_y + (start_y % 1000) * pixel_scale_y;
		for (int y = start_y + 1; y < stop_y + 1; y++) {
			int n = 0;
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
			draw_matrix[x - 1][y - 1] = n;
			yy += pixel_scale_y;
		}
		xx += pixel_scale_x;
	}
}

void Mandelbrot::mandelbrot_set_MC(int start_x, int stop_x, int start_y, int stop_y) {

	for (int x = 0; x < GRID; x++) {
		for (int y = 0; y < GRID; y++) {
			threads[y * GRID + x] = new std::thread(mandelbrot_set_SC, x * (1000 / GRID) + start_x, (x + 1) * 1000 / GRID + stop_x - start_x, x_coord, x_pixel_scale, y * (1000 / GRID), (y + 1) * 1000 / GRID, y_coord, y_pixel_scale, iterations, infinity, pixel_matrix);
		}
	}
	for (int i = 0; i < GRID * GRID; i++) {
		threads[i]->join();
		delete(threads[i]);
	}
}