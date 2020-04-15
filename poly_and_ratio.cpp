#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include "modular_arithmetic.hpp"
#include "poly_and_ratio.hpp"


using std::unordered_map;
using std::string;
using std::vector;


inline void split(const string& str, uint_fast16_t* cont, string delims = " ")
{
	std::size_t current = str.find(delims), end = str.size();
	string s1 = str.substr(0, current), s2 = str.substr(current + 1, end - 1);
	cont[0] = stoi(s1);
	cont[1] = stoi(s2);
}


bool compare_degrees(const string& a, const string& b)
{
	uint_fast16_t cont1[2], cont2[2];
	split(a, cont1, ", ");
	split(b, cont2, ", ");
 	return (cont1[0] + cont1[1]) > (cont2[0] + cont2[1]) && (!(cont1[0] + cont1[1]) == (cont2[0] + cont2[1])
		|| (cont1[0] > cont2[0] || cont1[1] > cont2[1]));
}



Poly::Poly(unordered_map<string, Galois>& data, int_fast64_t mod)
{
	this->mod = mod;
	for (std::pair<const string, Galois>& el : data)
	{
		if (el.second.get_mod() != mod)
		{
			throw "mods must be equal";
		}
	}
	this->data = data;
}

Poly::Poly(uint_fast32_t mod)
{
	this->mod = mod;
	data.emplace("0, 0", Galois(0, mod));
}

Poly Poly::operator+ (const Poly& other)
{
	Poly res(*this);
	for (const std::pair<const string, Galois>& el : other.data)
	{
		if (res.data.find(el.first) != res.data.end())
		{
			res.data[el.first] += el.second;
		}
		else
		{
			res.data[el.first] = el.second;
		}
	}

	return res;
}

Poly Poly::operator* (const Galois& other)
{
	Poly res(*this);
	for (const std::pair<const string, Galois>& el : res.data)
	{
		res.data[el.first] *= other;
	}

	return res;
}

Poly Poly::operator*(const Poly& other)
{
	Poly res = Poly(this->mod);

	uint_fast16_t sum1, sum2, degrees1[2], degrees2[2];
	string key;
	for (const std::pair<const string, Galois>& el1 : other.data)
	{
		split(el1.first, degrees1, ", ");
		for (std::pair<const string, Galois>& el2 : this->data)
		{
			split(el2.first, degrees2, ", ");
			sum1 = degrees1[0] + degrees2[0];
			sum2 = degrees1[1] + degrees2[1];
			key = std::to_string(sum1) + ", " + std::to_string(sum2);
			if (res.data.find(key) != res.data.end())
			{
				res.data[key] += el2.second * el1.second;
			}
			else
			{
				res.data[key] = el2.second * el1.second;
			}
		}
	}

	return res;
}

Galois Poly::value(Galois& x, Galois& y)
{
	Galois res = Galois(0, this->mod), x_pow, y_pow;
	uint_fast16_t degrees[2];
	for (std::pair<const string, Galois>& el : this->data)
	{
		split(el.first, degrees, ", ");
		res += el.second * x.pow(degrees[0]) * y.pow(degrees[1]);
	}

	return res;
}

string Poly::get_str()
{
	vector<string> keys;
	keys.reserve(this->data.size());
	for (std::pair<const string, Galois>& el : this->data)
	{
		keys.push_back(el.first);
	}

	std::sort(keys.begin(), keys.end(), compare_degrees);
	string res = "";
	uint_fast16_t degree[2];
	for (string& key : keys)
	{
		split(key, degree, ", ");
		res += std::to_string(this->data[key].get_value()) +
			"*x^" + std::to_string(degree[0]) +
			"*y^" + std::to_string(degree[1]) +
			+" + ";
	}

	return res.substr(0, res.size() - 3);
}

int_fast16_t Poly::get_mod()
{
	return this->mod;
}

unordered_map<string, Galois> Poly::get_data()
{
	return this->data;
}


Ratio::Ratio(Poly& p1, Poly& p2)
{
	if (p1.get_mod() != p2.get_mod())
	{
		throw "mods of polynomials must be equal";
	}
	this->numerator = p1;
	this->denominator = p2;
}

Ratio::Ratio(uint_fast32_t mod)
{
	this->numerator = Poly(mod);
	this->denominator = Poly(mod);
}

Ratio Ratio::operator* (const Ratio& other)
{
	Poly n = this->numerator * other.numerator, d = this->denominator * other.denominator;
	return Ratio(n, d);
}

Ratio Ratio::operator* (const Poly& other)
{
	Poly n = this->numerator * other;
	return Ratio(n, this->denominator);
}

Ratio Ratio::operator* (const Galois& other)
{
	Poly n = this->numerator * other;
	return Ratio(n, this->denominator);
}

string Ratio::get_str()
{
	return "(" + this->numerator.get_str() + ") / (" + this->denominator.get_str() + ")";
}

Galois Ratio::value(Galois& x, Galois& y)
{
	return (this->numerator.value(x, y)) / (this->denominator.value(x, y));
}

