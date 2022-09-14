#pragma once
class Positionable {

public:
	Positionable(double x_coord, double y_coord, double window_width, double window_height);
	~Positionable();
	double x_coord, y_coord;
	double x_min, y_min;
	double x_distance, y_distance;
	double x_pixel_scale, y_pixel_scale;
	int fractal_space_x, fractal_space_y;

};

class Drawable {

public:
	Drawable(int start_x, int stop_x, int start_y, int stop_y, int** pixel_matrix);
	~Drawable();
	void set_new_window(int start_x, int stop_x, int start_y, int stop_y);
	int** pixel_matrix;
	int start_x, stop_x;
	int start_y, stop_y;
	int width, height;
};
