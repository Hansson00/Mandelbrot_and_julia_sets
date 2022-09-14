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


