#include <cstdint>
#include "modular_arithmetic.hpp"
#include "elliptic_curve.hpp"



Point::Point(Galois x, Galois y)
{
	if (x.get_mod() != y.get_mod())
	{
		throw "mods of x and y must be equal";
	}
	this->x = x;
	this->y = y;
	this->is_infinity = false;
}

Point::Point(bool is_infinity)
{
	this->is_infinity = true;
}

bool Point::operator== (const Point& other)
{
	return ((this->x == other.x) && (this->y == other.y));
}

Point Point::operator-()
{
	return Point(this->x, -(this->y));
}

bool Point::isinfty()
{
	return this->is_infinity;
}

Galois Point::get_x()
{
	return this->x;
}

Galois Point::get_y()
{
	return this->y;
}


EllipticCurve::EllipticCurve(int_fast64_t a, int_fast64_t b, int_fast64_t q)
{
	this->a = Galois(a, q);
	this->b = Galois(b, q);
	this->q = q;
}
EllipticCurve::EllipticCurve() {}

bool EllipticCurve::is_point_on_curve(Point &P)
{
	return P.isinfty() || (P.get_y().pow(2) == P.get_x().pow(3) + (this->a) * P.get_x() + (this->b));
}

Point EllipticCurve::double_point(Point &P)
{
	if (P.isinfty() || P.get_y() == 0)
	{
		return Point(true);
	}
	Galois lambda = (P.get_x().pow(2) * 3 + this->a) / (P.get_y() * 2);
	Galois x_r = lambda.pow(2) - (P.get_x() * 2);
	return Point(x_r, lambda * (P.get_x() - x_r) - P.get_y());
}

Point EllipticCurve::add_points(Point &P, Point &Q)
{
	if (P.isinfty())
	{
		return Q;
	}
	if (Q.isinfty())
	{
		return P;
	}

	if (Q == P)
	{
		return this->double_point(P);
	}

	if (P.get_x() == Q.get_x())
	{
		return Point(true);
	}

	Galois lambda = (P.get_y() - Q.get_y()) / (P.get_x() - Q.get_x());
	Galois x_r = lambda.pow(2) - P.get_x() - Q.get_x();
	return Point(x_r, lambda * (P.get_x() - x_r) - P.get_y());
}

Point EllipticCurve::sub_points(Point& P, Point& Q)
{
	Point Q_min = -Q;
	return add_points(P, Q_min);
}
