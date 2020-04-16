/**
* ��������� �������, �� ���������� ����, ��� ��������� ����� ����� P �� Q,
* �� �������� �������� ����� E �� ������� �� �������� ����� E � ����� P
* ����� 2.3 �������
*/
#include "poly_and_ratio.hpp"
#include "elliptic_curve.hpp"

#ifndef CALC_LINES_H
#define CALC_LINES_H

/**
* �������� ����, ��� ��������� ����� ����� P �� Q, �� �������� �������� ����� E
*/
Poly calc_line(Point& P, Point& Q, EllipticCurve& E);

/**
* �������� ������� �� �������� ����� E � ����� P
*/
Poly calc_tangent(Point& P, EllipticCurve& E);

#endif
