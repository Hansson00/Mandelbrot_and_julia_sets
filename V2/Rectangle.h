#pragma once
#include "Vector2.h"

/** Double rectangle **/

class RectangleD
{
public:
	
	/** Construct empty rectangle at 0.0 ,0.0. */
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

	/** Width of the rectangle*/
	double width;

	/** Height of the rectangle*/
	double height;

	/** Position of the rectangle*/
	Vector2d position;
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

	/** Construct empty rectangle at 0.0 ,0.0. */
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
	RectangleI(double width, double height, const Vector2d& position);

	/** Width of the rectangle*/
	double width;

	/** Height of the rectangle*/
	double height;

	/** Position of the rectangle*/
	Vector2d position;
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
RectangleI& operator*=(RectangleI& v1, int d1);

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
RectangleI& operator/=(RectangleI& v1, int d1);