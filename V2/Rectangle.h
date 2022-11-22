#pragma once
#include "Vector2.h"
#include "SDL.h"

/** Double rectangle **/

class RectangleD
{
public:
	
	/* Construct empty rectangle at 0.0 ,0.0. */
	RectangleD();

	/*
	* Construct a double rectangle with width and height at position.
	* 
	* @param width
	*	Width of the rectangle.
	* 
	* @param height
	*	Height of the rectangle.
	* 
	* @param position
	*	Position of rectangle.
	*/
	RectangleD(double width, double height, const Vector2d& position);

	/* (double) Width of the rectangle*/
	double width;

	/* (double) Height of the rectangle*/
	double height;

	/* Position of the rectangle*/
	Vector2d position;

	/*
	* Translates the position on this Rectangle with a given vector
	* 
	* @param mouse_pos
	*	A vector which tells how direction and how far the rectangle should move
	*/
	void translate(const Vector2d& mouse_pos);
};


/*
* Multiplies the size of the rectangle.
* 
* @param v1
*	Rectangle which is going to be resized.
* 
* @param d1
*	Scale parameter.
* 
* @returns
*	v1 *= d1
*/
RectangleD& operator*=(RectangleD& v1, double d1);

/*
* Divides the size of the rectangle.
*
* @param v1
*	Rectangle which is going to be resized.
*
* @param d1
*	Scale parameter.
*
* @returns
*	v1 /= d1
*/
RectangleD& operator/=(RectangleD& v1, double d1);

/** Int rectangle **/

class RectangleI
{
public:

	/* Construct empty rectangle at 0.0 ,0.0. */
	RectangleI();

	/*
	* Construct a double rectangle with width and height at position.
	*
	* @param width
	*	Width of the rectangle.
	*
	* @param height
	*	Height of the rectangle.
	*
	* @param position
	*	Position of rectangle.
	*/
	RectangleI(uint32_t width, uint32_t height, const Vector2i& position);

	/* (uint32_t) Width of the rectangle*/
	uint32_t width;

	/* (uint32_t) Height of the rectangle*/
	uint32_t height;

	/* Position of the rectangle*/
	Vector2i position;
};


/*
* Multiplies the size of the rectangle.
*
* @param v1
*	Rectangle which is going to be resized.
*
* @param d1
*	Scale parameter.
*
* @returns
*	v1 *= d1
*/
RectangleI& operator*=(RectangleI& v1, uint32_t d1);

/*
* Divides the size of the rectangle.
*
* @param v1
*	Rectangle which is going to be resized.
*
* @param d1
*	Scale parameter.
*
* @returns
*	v1 /= d1
*/
RectangleI& operator/=(RectangleI& v1, uint32_t d1);