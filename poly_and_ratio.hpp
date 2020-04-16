/**
* Реалізація класів поліном та раціональна функція, коефіцієнти яких належать деякому кільцю лишків
*/
#include <unordered_map>
#include <string>
#include "modular_arithmetic.hpp"


#ifndef POLY_AND_RATIO_H
#define POLY_AND_RATIO_H


/**
* Клас поліном
* data - хеш-таблиця коефіцієнтів Galois, в якій ключ має мати вигляд "m, k",
* що відповідає моному x^m * y^k, де k, m є невід'ємними цілими числами
* параметр mod визначає якому кільцю лишків мають належати коефіцієнти
*/
class Poly
{
private:
	std::unordered_map<std::string, Galois> data;
	int_fast64_t mod;

public:
	Poly(std::unordered_map<std::string, Galois>& data, int_fast64_t mod);

	/**
	* Створює поліном 0 * x^0 * y^0 з коефіцієнтами, які належать кільцю лишків по модулю mod
	*/
	Poly(uint_fast32_t mod);

	Poly() {}

	Poly operator+ (const Poly& other);

	Poly operator* (const Poly& other);

	Poly operator* (const Galois& other);

	/**
	* Повертає значення полінома в точці (x, y)
	*/
	Galois value(Galois& x, Galois& y);

	/**
	* Повертає строкове представлення полінома
	*/
	std::string get_str();

	int_fast16_t get_mod();

	/**
	* Повертає хеш-таблицю коефіцієнтів полінома
	*/
	std::unordered_map<std::string, Galois> get_data();
};


/**
* Клас раціональна функція
* numerator, denominator - поліноми, які мають коефіцієнти з одного кільця лишків
*/
class Ratio
{
private:
	Poly numerator, denominator;

public:
	Ratio(Poly& p1, Poly& p2);

	Ratio(uint_fast32_t mod);

	Ratio operator* (const Ratio& other);

	Ratio operator* (const Poly& other);

	Ratio operator* (const Galois& other);

	/**
	* Повертає строкове представлення раціональної функції
	*/
	std::string get_str();

	/**
	* Повертає значення раціональної функції в точці (x, y)
	*/
	Galois value(Galois& x, Galois& y);
};

#endif
