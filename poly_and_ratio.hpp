/**
* ��������� ����� ������ �� ����������� �������, ����������� ���� �������� ������� ����� �����
*/
#include <unordered_map>
#include <string>
#include "modular_arithmetic.hpp"


#ifndef POLY_AND_RATIO_H
#define POLY_AND_RATIO_H


/**
* ���� ������
* data - ���-������� ����������� Galois, � ��� ���� �� ���� ������ "m, k",
* �� ������� ������ x^m * y^k, �� k, m � ����'������ ������ �������
* �������� mod ������� ����� ����� ����� ����� �������� �����������
*/
class Poly
{
private:
	std::unordered_map<std::string, Galois> data;
	int_fast64_t mod;

public:
	Poly(std::unordered_map<std::string, Galois>& data, int_fast64_t mod);

	/**
	* ������� ������ 0 * x^0 * y^0 � �������������, �� �������� ����� ����� �� ������ mod
	*/
	Poly(uint_fast32_t mod);

	Poly() {}

	Poly operator+ (const Poly& other);

	Poly operator* (const Poly& other);

	Poly operator* (const Galois& other);

	/**
	* ������� �������� ������� � ����� (x, y)
	*/
	Galois value(Galois& x, Galois& y);

	/**
	* ������� �������� ������������� �������
	*/
	std::string get_str();

	int_fast16_t get_mod();

	/**
	* ������� ���-������� ����������� �������
	*/
	std::unordered_map<std::string, Galois> get_data();
};


/**
* ���� ����������� �������
* numerator, denominator - �������, �� ����� ����������� � ������ ����� �����
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
	* ������� �������� ������������� ����������� �������
	*/
	std::string get_str();

	/**
	* ������� �������� ����������� ������� � ����� (x, y)
	*/
	Galois value(Galois& x, Galois& y);
};

#endif
