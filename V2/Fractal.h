#pragma once
#include "Rectangle.h"
#include "SDL.h"
class Fractal
{
public:
	/*
	* Constructs a fractal at a given rectangle in space drawing to a given matrix.
	* 
	* @param rect
	*	A rectangle in space which the fractal will be drawn to.
	* 
	* @param matrix
	*	A MxN matrix which the fractal will be drawn to.
	*
	* @param fractal_pointer
	*	Takes a fractal_function pointer which the class will run
	*/
	Fractal(const RectangleD& rect, uint32_t** matrix, void (*fractal_pointer)(void));

	/** Deconstructor. */
	~Fractal();

	/** Rectangle in space. */
	RectangleD space_rect;

	/** Matrix which the fractal will be drawn to. */
	uint32_t** matrix;

private:
	/** A pointer which decides which fractal will be run*/
	void (*fractal_pointer)(void);
};


/*
* Runs the mandelbrot fractal algorith for every pixel in a given matrix.
* 
* @param space_rect
*	A double rectangle in space which contains the fractal
* 
* @param maxtrix
*	A matrix which the result will be printed on 
* 
* @param matrix_rect
*	Tells the function where in the matrix the fractal is operating
* 
* @param infinity
*	What the fractal considers infinity. Recommended ~(infinity > 20)
* 
* @param iterations 
*	How many iterations before stoping where the fractal considers a point in space not going to infinity.
*/
void mandelbrot_fractal(const RectangleD& space_rect, const RectangleI& matrix_rect, uint32_t** matrix, uint32_t infinity, uint32_t iterations);

