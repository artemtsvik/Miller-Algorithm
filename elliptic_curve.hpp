#include <cstdint>
#include "modular_arithmetic.hpp"

#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H

class Point
{
private:
	Galois x, y;
	bool is_infinity;

public:
	Point(Galois x, Galois y);

	Point(bool is_infinity);

	bool operator== (const Point& other);

	Point operator- ();

	bool isinfty();

	Galois get_x();

	Galois get_y();
};

class EllipticCurve
{
private:
	Galois a, b;
	int_fast64_t q;

public:
	EllipticCurve(int_fast64_t a, int_fast64_t b, int_fast64_t q);
	EllipticCurve();

	bool is_point_on_curve(Point& P);

	Point double_point(Point& P);

	Point add_points(Point& P, Point& Q);

	Point sub_points(Point& P, Point& Q);
};


#endif