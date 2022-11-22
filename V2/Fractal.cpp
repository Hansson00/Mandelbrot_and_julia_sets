#include "Fractal.h"

Fractal::Fractal(const RectangleD& space_rect, const RectangleI& matrix_rect,uint32_t** matrix,
	void(*fractal_pointer)(const RectangleD&,
	const RectangleI&,uint32_t**, uint32_t, uint32_t)) :
	space_rect(space_rect), matrix_rect(matrix_rect), matrix(matrix), fractal_pointer(fractal_pointer)
{
}

void Fractal::generate_fractal(uint32_t infinity, uint32_t iterations)
{
	static std::thread* threads = new std::thread[4];

	for (uint32_t i = 0; i < 2; i++)
	{

		for (uint32_t j = 0; j < 2; j++)
		{
			RectangleI tmp = { matrix_rect.height / 2, matrix_rect.width / 2, { i * matrix_rect.height / 2, j * matrix_rect.width / 2} };
			threads[i+j*2] = std::thread(fractal_pointer, space_rect, tmp, matrix, infinity, iterations);
		}
	}
	
	for (uint32_t i = 0; i < 4; i++)
	{
		threads[i].join();
	}

}

void Fractal::translate(const Vector2d& mouse_pos)
{
	translate(mouse_pos, 1);
}

void Fractal::translate(const Vector2d& mouse_pos, double scaling)
{
	const double matrix_width =  (double) matrix_rect.width;
	const double matrix_height = (double) matrix_rect.height;

	/* Rescales x and y to position relative to center of the screen. */
	const double x_coord = mouse_pos.x - matrix_width / 2;
	const double y_coord = mouse_pos.y - matrix_height / 2;

	/* 
	* Create an ofset and add it to the existing fractal space.
	* Scaling is used in case the user want a smaller or larger shift towards the mouse.
	* Finaly, the coodinates are scaled down to pixel width and height in fractal space
	*/
	space_rect.position += 
	  {x_coord * scaling * space_rect.width  / matrix_height,
	   y_coord * scaling * space_rect.height / matrix_height};
}




namespace fractals
{
void mandelbrot_fractal(
	const RectangleD& space_rect,
	const RectangleI& matrix_rect,
	uint32_t** matrix,
	uint32_t infinity,
	uint32_t iterations)
{
	// Used for complex calculations.
	double a, b, twoab, aa = 0, bb = 0;

	// Handels amount of iterations in the fractal.
	uint16_t n = 0;

	// Creates a space in the matrix where the fractal is running.
	// X constans.
	const uint16_t start_x = matrix_rect.position.x;
	const uint16_t stop_x = matrix_rect.position.x + matrix_rect.width;
	const double scale_x = space_rect.width / (double)matrix_rect.width;
	// Y constans.
	const uint16_t start_y = matrix_rect.position.y;
	const uint16_t stop_y = matrix_rect.position.y + matrix_rect.height;
	const double scale_y = space_rect.height / (double)matrix_rect.height;

	// Handles the position within the fractal space.
	double space_xpos, space_ypos;

	for (uint16_t i = start_x; i < stop_x; i++)
	{
		// Sets x to the correct pixel in fractal space.
		space_xpos = space_rect.position.x - space_rect.width / 2 + scale_x * i;

		for (uint16_t j = start_y; j < stop_y; j++)
		{
			// Sets y to the correct pixel in fractal space.
			space_ypos = space_rect.position.y - space_rect.height / 2 + scale_y * j;

			// Resets iterations from last run.
			n = 0;

			// Assings values before complex calculations.
			a = space_xpos;
			b = space_ypos;

			// Mandlebrot fractal algorith.
			do {
				aa = a * a;
				bb = b * b;
				twoab = 2.0 * a * b;
				a = aa - bb + space_xpos;
				b = twoab + space_ypos;
				n++;
			} while (n < iterations && aa * aa + bb * bb < infinity);

			// Sets the amount of iterations for this pixel.
			matrix[i][j] = n;
		}
	}
}
}