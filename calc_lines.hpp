#include "poly_and_ratio.hpp"
#include "elliptic_curve.hpp"

#ifndef CALC_LINES_H
#define CALC_LINES_H

Poly calc_line(Point& P, Point& Q, EllipticCurve& E);

Poly calc_tangent(Point& P, EllipticCurve& E);

#endif
