#include <string>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include "calc_lines.hpp"

#define DEBUG 1


using std::unordered_map;
using std::string;

#if DEBUG
string print_bits(uint_fast32_t s)
{
	string res;
	uint_least32_t x = 1UL;

	for (int i = 0; i != 32; i++)
	{
		res = ((x & s) ? "1" : "0") + res;
		x <<= 1;
	}
	return res;
}
#endif


Ratio miller_algorithm(EllipticCurve& E, Point& P, uint_fast32_t r)
{
	if (!E.is_point_on_curve(P))
	{
		throw "point must be on curve";
	}

	Point R = P;

	unordered_map<string, Galois> coefs;
	coefs["0, 0"] = Galois(1, E.get_mod());
	Poly p1 = Poly(coefs, E.get_mod());

	Ratio f = Ratio(p1, p1);
	uint_fast32_t i = 1UL << 31;
	
	while (!(r & i))
	{
		i >>= 1;
	}

#if DEBUG
	std::cout << "r = " << print_bits(r) << std::endl
		<< "i = " << print_bits(i) << std::endl << std::endl;
#endif

	Poly l, v;

	while (i >>= 1)
	{
		l = calc_tangent(R, E);
		R = E.double_point(R);

		v = calc_line(R, R, E);
		f = f * f * Ratio(l, v);

#if DEBUG
		std::cout << "i = " << (uint_fast32_t)log2(i) << std::endl
			<< "r_i = " << bool(r & i) << std::endl
			<< "l_{R,R}: " << l.get_str() << std::endl
			<< "R = " << R.get_str() << std::endl
			<< "v_R: " << v.get_str() << std::endl
			<< "f = " << f.get_str() << std::endl;
#endif

		if (r & i)
		{
			l = calc_line(R, P, E);
			R = E.add_points(R, P);

			v = calc_line(R, R, E);
			f = f * Ratio(l, v);

#if DEBUG
			std::cout << "l_{R,R}: " << l.get_str() << std::endl
				<< "R = " << R.get_str() << std::endl
				<< "v_R: " << v.get_str() << std::endl
				<< "f = " << f.get_str() << std::endl;
#endif

		}

#if DEBUG
		std::cout << std::endl;
#endif

	}

	return f;
}


int main()
{
	uint_fast32_t p;
	do
	{
		std::cout << "Enter p (must be prime):" << std::endl
			<< "p = ";
		std::cin >> p;
	} while (!isprime(p));

	int_fast64_t a, b;
	std::cout << std::endl << "Enter a and b for elliptic curve E: y^2 = x^3 + a*x + b" << std::endl
		<< "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;

	int_fast64_t x_, y_;
	std::cout << std::endl << "Enter point P = (x, y)" << std::endl
		<< "x = ";
	std::cin >> x_;
	std::cout << "y = ";
	std::cin >> y_;

	EllipticCurve E = EllipticCurve(a, b, p);
	Galois x = Galois(x_, p), y = Galois(y_, p);
	Point P = Point(x, y);

	std::cout << std::endl << "Calculate:" << std::endl;
	Ratio f = miller_algorithm(E, P, 5);

	std::cout << "Result:" << std::endl;
	std::cout << f.get_str() << std::endl;

	system("pause");
	return 0;
}