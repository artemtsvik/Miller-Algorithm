/**
* Реалізація функцій, які обчислюють січну, яка проходить через точки P та Q,
* які належать еліптичній кривій E та дотичну до еліптичної кривої E в точці P
* розділ 2.3 курсової
*/
#include "poly_and_ratio.hpp"
#include "elliptic_curve.hpp"

#ifndef CALC_LINES_H
#define CALC_LINES_H

/**
* Обчислює січну, яка проходить через точки P та Q, які належать еліптичній кривій E
*/
Poly calc_line(Point& P, Point& Q, EllipticCurve& E);

/**
* Обчислює дотичну до еліптичної кривої E в точці P
*/
Poly calc_tangent(Point& P, EllipticCurve& E);

#endif
