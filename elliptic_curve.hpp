/**
* Реалізація класів точки, координати якої належать деякому кільцю лишків, 
* та еліптичної кривої над полем лишків
* розділ 2.4 курсової
*/
#include <cstdint>
#include <string>
#include "modular_arithmetic.hpp"

#ifndef ELLIPTIC_CURVE_H
#define ELLIPTIC_CURVE_H


/**
* Точка, координати якої x та y належать деякому кільцю лишків.
* Якщо булева змінна is_infinity = true, то це нескінченно віддалена точка
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
	* Конструктор для створення нескінченно віддаленої точки.
	* is_infinity має дорівнювати true. При false коректна робота не гарантується.
	*/
	Point(bool is_infinity);

	bool operator== (const Point& other);

	bool operator!= (const Point& other);

	Point operator- ();

	/**
	* Повертає true якщо точка є нескінченно віддаленою, false - в іншому випадку
	*/
	bool isinfty();

	/**
	* Повертає координату x
	*/
	Galois get_x();

	/**
	* Повертає координату y
	*/
	Galois get_y();

	/**
	* Повертає строкове представлення
	* Якщо точка скінченна, то воно матиме вигляд (x, y). Якщо нескінченно віддалена - (infty).
	*/
	std::string get_str();
};


/**
* Еліптична крива, яка має вигляд y^2 = x^3 + a*x + b.
* Для коректної роботи методів double_point, add_points, sub_points параметр q, 
* який визначає якому кільцю лишків мають належати координати точок кривої, має бути простим
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
	* Повертає true якщо точка P належить кривій, false - в іншому випадку
	*/
	bool is_point_on_curve(Point& P);

	/**
	* Подвоєння точки P на еліптичній кривій
	*/
	Point double_point(Point& P);

	/**
	* Додавання точок P та Q на еліптичній кривій
	*/
	Point add_points(Point& P, Point& Q);

	/**
	* Віднімання точок P та Q на еліптичній кривій
	*/
	Point sub_points(Point& P, Point& Q);

	/**
	* Повертає порядок точки r, де r * P = (infty)
	*/
	int_fast64_t order(Point& P);

	/**
	* Повертає значення параметра q
	*/
	int_fast64_t get_mod();

	/**
	* Повертає значення коефіцієнта a
	*/
	Galois get_a();

	/**
	* Повертає значення коефіцієнта b
	*/
	Galois get_b();
};


#endif