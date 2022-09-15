#include "Positionable.h"

Positionable::Positionable(double x_coord, double y_coord, double fractal_space_x, double fractal_space_y){
	
	this->x_coord = x_coord;
	this->y_coord = y_coord;
	this->fractal_space_x = fractal_space_x;
	this->fractal_space_y = fractal_space_y;
	x_distance = fractal_space_x * 3 / 1000;
	y_distance = fractal_space_y * 3 / 1000;
	x_pixel_scale = x_distance / fractal_space_x;
	y_pixel_scale = y_distance / fractal_space_y;
	x_min = x_coord - fractal_space_x / 2 * x_pixel_scale;
	y_min = y_coord - fractal_space_y / 2 * y_pixel_scale;
}

Positionable::~Positionable() {
}

void Positionable::zoom(long double times) {
	x_distance /= times;
	y_distance /= times;
	x_pixel_scale = x_distance / (double)fractal_space_x;
	y_pixel_scale = y_distance / (double)fractal_space_y;
	x_min = x_coord - (double)fractal_space_x / 2 * x_pixel_scale;
	y_min = y_coord - (double)fractal_space_y / 2 * y_pixel_scale;
}



Drawable::Drawable(int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix){
	this->start_x = start_x;
	this->stop_x = stop_x;
	this->start_y = start_y;
	this->stop_y = stop_y;
	this->pixel_matrix = pixel_matrix;
	width = stop_x - start_x;
	height = stop_y - start_y;
}

Drawable::~Drawable() {
}

void Drawable::set_new_window(int start_x, int stop_x, int start_y, int stop_y) {
	this->start_x = start_x;
	this->stop_x = stop_x;
	this->start_y = start_y;
	this->stop_y = stop_y;
	width = stop_x - start_x;
	height = stop_y - start_y;
}

bool Drawable::hitbox(int x, int y) {

	if (x >= start_x && x <= stop_x)
		if (y >= start_y && y <= stop_y)
			return true;
	return false;
}


Threading::Threading(int threads, int width, int height) {
	this->threads = 1;
	thread_pattern();
}

Threading::~Threading() {
	delete(thread_arr);
}

void Threading::add_threads(int n) {
	if (threads + n <= MAX_THREADS && threads + n >= 1)
		threads += n;
	thread_pattern();
}

void Threading::thread_pattern() {

	int max = 1;
	th_x = 1;
	th_y = 1;

	for (int i = 1; i <= std::min((int)(sqrt(MAX_THREADS)), threads); i++)
		for (int j = 1; j <= i; j++)
			if (i * j <= MAX_THREADS && i * j > max && i * j <= threads)
				if (this->width % i == 0 && this->height % j == 0) {
					max = i * j;
					th_x = i;
					th_y = j;
				}
}

int Threading::get_threads(int i) {
	if (i == 0) return th_x;
	else return th_y;
}

int Threading::get_wanted_threads() {
	return threads;
}
