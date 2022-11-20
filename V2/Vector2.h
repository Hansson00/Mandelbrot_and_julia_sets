#pragma once

/** Double Vector **/

class Vector2d
{
public:
	/** Construct floating vector at 0,0. */
	Vector2d();

	/*
	* Construct a new vector with x and y component.
	* 
	* @param x
	*	X component.
	* 
	* @param y
	*	Y component.
	*/
	Vector2d(double x, double y);

	/** X component. */
	double x;
	/** Y component. */
	double y;
};


/*
* Add two vector2ds together resulting in a new vector.
*
* @param v1
*	Vector to add.
*
* @param v2
*	Vector to add.
* 
* @retruns
*	v1 + v2.
*/
Vector2d operator+(const Vector2d& v1, const Vector2d& v2);

/*
* Add one vector to an already existing one.
*
* @param v1
*	Vector to be changed.
*
* @param v2
*	Vector to add.
*
* @retruns
*	v1 += v2.
*/
Vector2d& operator+=(Vector2d& v1, const Vector2d& v2);

/** Integer Vector **/

class Vector2i
{
public:
	/** Construct and int vector at 0,0.*/
	Vector2i();

	/*
	* Construct a new vector with x and y component.
	*
	* @param x
	*	X component.
	*
	* @param y
	*	Y component.
	*/
	Vector2i(int x, int y);

	/** X component. */
	int x;
	/** Y component. */
	int y;
};


/*
* Add two vector2is together resulting in a new vector.
*
* @param v1
*	Vector to add.
*
* @param v2
*	Vector to add.
*
* @retruns
*	v1 + v2.
*/
Vector2i operator+(const Vector2i& v1, const Vector2i& v2);

/*
* Add one vector to an already existing one.
*
* @param v1
*	Vector to be changed.
*
* @param v2
*	Vector to add.
*
* @retruns
*	v1 += v2.
*/
Vector2i& operator+=(Vector2i& v1, const Vector2i& v2);