#include <string>
#include <unordered_map>
#include "modular_arithmetic.hpp"
#include "elliptic_curve.hpp"
#include "poly_and_ratio.hpp"
#include "calc_lines.hpp"


using std::string;
using std::unordered_map;


Poly calc_line(Point& P, Point& Q, EllipticCurve& E)
{
	unordered_map<string, Galois> data;
	if (P.isinfty() && Q.isinfty())
	{
		data["0, 0"] = Galois(1, E.get_mod());
	}
	else if (Q.get_x() != P.get_x())
	{
		data["0, 0"] = Q.get_x() * P.get_y() - P.get_x() * Q.get_y();
		data["1, 0"] = Q.get_y() - P.get_y();
		data["0, 1"] = P.get_x() - Q.get_x();
	}
	else
	{
		data["0, 0"] = -P.get_x();
		data["1, 0"] = Galois(1, E.get_mod());
	}

	return Poly(data, E.get_mod());
}


Poly calc_tangent(Point& P, EllipticCurve& E)
{
	unordered_map<string, Galois> data;
	if (P.get_y() == 0)
	{
		data["0, 0"] = -P.get_x();
		data["1, 0"] = Galois(1, E.get_mod());
	}
	else
	{
		data["0, 0"] = -P.get_y().pow(2) + (E.get_a() * P.get_x() * 2) + (E.get_b() * 3);
		data["0, 1"] = -P.get_y() * 2;
		data["1, 0"] = (P.get_x().pow(2) * 3) + E.get_a();
	}

	return Poly(data, E.get_mod());
}

