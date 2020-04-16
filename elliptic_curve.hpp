/**
* ��������� ����� �����, ���������� ��� �������� ������� ����� �����, 
* �� �������� ����� ��� ����� �����
* ����� 2.4 �������
*/
#include <cstdint>
#include <string>
#include "modular_arithmetic.hpp"

#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H


/**
* �����, ���������� ��� x �� y �������� ������� ����� �����.
* ���� ������ ����� is_infinity = true, �� �� ���������� �������� �����
*/
class Point
{
private:
	Galois x, y;
	bool is_infinity;

public:
	Point() {}

	Point(Galois x, Galois y);

	/**
	* ����������� ��� ��������� ���������� �������� �����.
	* is_infinity �� ���������� true. ��� false �������� ������ �� �����������.
	*/
	Point(bool is_infinity);

	bool operator== (const Point& other);

	bool operator!= (const Point& other);

	Point operator- ();

	/**
	* ������� true ���� ����� � ���������� ���������, false - � ������ �������
	*/
	bool isinfty();

	/**
	* ������� ���������� x
	*/
	Galois get_x();

	/**
	* ������� ���������� y
	*/
	Galois get_y();

	/**
	* ������� �������� �������������
	* ���� ����� ��������, �� ���� ������ ������ (x, y). ���� ���������� �������� - (infty).
	*/
	std::string get_str();
};


/**
* �������� �����, ��� �� ������ y^2 = x^3 + a*x + b.
* ��� �������� ������ ������ double_point, add_points, sub_points �������� q, 
* ���� ������� ����� ����� ����� ����� �������� ���������� ����� �����, �� ���� �������
*/
class EllipticCurve
{
private:
	Galois a, b;
	int_fast64_t q;

public:
	EllipticCurve(int_fast64_t a, int_fast64_t b, int_fast64_t q);
	EllipticCurve();

	/**
	* ������� true ���� ����� P �������� �����, false - � ������ �������
	*/
	bool is_point_on_curve(Point& P);

	/**
	* �������� ����� P �� �������� �����
	*/
	Point double_point(Point& P);

	/**
	* ��������� ����� P �� Q �� �������� �����
	*/
	Point add_points(Point& P, Point& Q);

	/**
	* ³������� ����� P �� Q �� �������� �����
	*/
	Point sub_points(Point& P, Point& Q);

	/**
	* ������� ������� ����� r, �� r * P = (infty)
	*/
	int_fast64_t order(Point& P);

	/**
	* ������� �������� ��������� q
	*/
	int_fast64_t get_mod();

	/**
	* ������� �������� ����������� a
	*/
	Galois get_a();

	/**
	* ������� �������� ����������� b
	*/
	Galois get_b();
};


#endif