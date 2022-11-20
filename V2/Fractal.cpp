#include "Fractal.h"

Fractal::Fractal(const RectangleD& rect, uint32_t** matrix, void(*fractal_pointer)(void)) :
	space_rect(rect), matrix(matrix), fractal_pointer(fractal_pointer)
{
}

Fractal::~Fractal()
{
}

void mandelbrot_fractal(
	const RectangleD& space_rect, 
	const RectangleI& matrix_rect, 
	uint32_t** matrix, 
	uint32_t infinity, 
	uint32_t iterations)
{	
	// Used for complex calculations.
	double a, b, twoab, aa, bb;	

	// Handels amount of iterations in the fractal.
	uint16_t n = 0;

	// Creates a space in the matrix where the fractal is running.
	// X constans.
	const uint16_t start_x = matrix_rect.position.x;
	const uint16_t stop_x  = matrix_rect.position.x + matrix_rect.width;
	const double scale_x = space_rect.width / (double)matrix_rect.width;
	// Y constans.
	const uint16_t start_y = matrix_rect.position.y;
	const uint16_t stop_y  = matrix_rect.position.y + matrix_rect.height;
	const double scale_y = space_rect.height / (double)matrix_rect.height;

	// Handles the position within the fractal space.
	double space_xpos, space_ypos;

	for (uint16_t i = start_x; i < stop_x; i++)
	{
		// Sets x to the correct pixel in fractal space.
		space_xpos = space_rect.position.x + scale_x * i;
		
		for (uint16_t j = start_y; j < stop_y; j++)
		{
			// Sets y to the correct pixel in fractal space.
			space_ypos = space_rect.position.y + scale_y * j;

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
