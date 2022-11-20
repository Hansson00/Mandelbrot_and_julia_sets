#include "Rectangle.h"

/** Double rectangle **/

RectangleD::RectangleD()
{
	RectangleD(0.0l, 0.0l, {});
}

RectangleD::RectangleD(double width, double height, const Vector2d& position):
	width(width), height(height), position(position)
{
}

RectangleD& operator*=(RectangleD& v1, double d1)
{
	v1.width *= d1;
	v1.height *= d1;
	return v1;
}

RectangleD& operator/=(RectangleD& v1, double d1)
{
	v1.width /= d1;
	v1.height /= d1;
	return v1;
}


/** Int rectangle **/

RectangleI::RectangleI()
{
	RectangleI(0.0l, 0.0l, {});
}

RectangleI::RectangleI(double width, double height, const Vector2d& position) :
	width(width), height(height), position(position)
{
}

RectangleI& operator*=(RectangleI& v1, int i1)
{
	v1.width *= i1;
	v1.height *= i1;
	return v1;
}

RectangleI& operator/=(RectangleI& v1, int i1)
{
	v1.width /= i1;
	v1.height /= i1;
	return v1;
}