#include "Vector2.h"

/** Double Vector **/

Vector2d::Vector2d()
{
	Vector2d(0.0l, 0.0l);
}

Vector2d::Vector2d(double x, double y):
	x(x), y(y)
{
}

Vector2d operator+(const Vector2d& v1, const Vector2d& v2)
{
	return Vector2d(v1.x + v2.x, v1.y + v2.y);
}

Vector2d& operator+=(Vector2d& v1, const Vector2d& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}

/** Int Vector **/

Vector2i::Vector2i()
{
	Vector2i(0, 0);
}

Vector2i::Vector2i(uint32_t x, uint32_t y) :
	x(x), y(y)
{
}

Vector2i operator+(const Vector2i& v1, const Vector2i& v2)
{
	return Vector2i(v1.x + v2.x, v1.y + v2.y);
}

Vector2i& operator+=(Vector2i& v1, const Vector2i& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}
