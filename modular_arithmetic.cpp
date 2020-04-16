#include <cstdint>
#include "modular_arithmetic.hpp"


uint_fast64_t bsqrt(uint_fast64_t a)
{
    uint64_t min = 0;
    uint64_t max = (1ULL << 32);
    while (true)
    {
        if (max <= 1 + min)
            return min;

        uint64_t sqt = min + (max - min) / 2;
        uint64_t sq = sqt * sqt;

        if (sq == a)
            return sqt;

        if (sq > a)
            max = sqt;
        else
            min = sqt;
    }
}


bool isprime(uint_fast64_t a)
{
    {
        uint_fast64_t i1, i2, i3, i4, i5, i6, i7, i8, bound;
        if (a == 0 || a == 1)
            return false;
        if (a == 2 || a == 3 || a == 5 || a == 7 || a == 11 || a == 13 || a == 17 || a == 19 || a == 23 || a == 29)
            return true;
        if (a % 2 == 0 || a % 3 == 0 || a % 5 == 0 || a % 7 == 0 || a % 11 == 0 || a % 13 == 0 || a % 17 == 0 || a % 19 == 0 || a % 23 == 0 || a % 29 == 0)
            return false;
        bound = bsqrt(a);
        i1 = 31; i2 = 37; i3 = 41; i4 = 43; i5 = 47; i6 = 49; i7 = 53; i8 = 59;
        while ((i8 <= bound) && (a % i1) && (a % i2) && (a % i3) && (a % i4) && (a % i5) && (a % i6) && (a % i7) && (a % i8))
        {
            i1 += 30; i2 += 30; i3 += 30; i4 += 30; i5 += 30; i6 += 30; i7 += 30; i8 += 30;
        }
        return !(i8 <= bound ||
            i1 <= bound && a % i1 == 0 ||
            i2 <= bound && a % i2 == 0 ||
            i3 <= bound && a % i3 == 0 ||
            i4 <= bound && a % i4 == 0 ||
            i5 <= bound && a % i5 == 0 ||
            i6 <= bound && a % i6 == 0 ||
            i7 <= bound && a % i7 == 0);
    }
}



Galois::Galois(int_fast64_t x, int_fast64_t n)
{
    if (n < 0)
    {
        throw "n must be positive";
    }
    mod = n;
    if (x < 0)
    {
        value = x % n + n;
    }
    else
    {
        value = x % n;
    }
}

Galois::Galois() {}

bool Galois::operator == (const Galois& other)
{
    return (this->value == other.value) && (this->mod == other.mod);
}

bool Galois::operator == (Galois& other)
{
    return (this->value == other.value) && (this->mod == other.mod);
}

bool Galois::operator == (int_fast64_t other)
{
    return this->value == other % this->mod;
}

bool Galois::operator != (const Galois& other)
{
    return (this->value != other.value) || (this->mod != other.mod);
}

bool Galois::operator != (int_fast64_t other)
{
    return this->value != other % this->mod;
}

Galois& Galois::operator = (const Galois& other)
{
    mod = other.mod;
    value = other.value;
    return *this;
}

Galois& Galois::operator = (int_fast64_t other)
{
    if (other < 0)
    {
        this->value = other % this->mod + this->mod;
    }
    else
    {
        this->value = other % this->mod;
    }
    return *this;
}

Galois Galois::operator+ (const Galois& other)
{
    if (this->mod != other.mod)
    {
        throw "Modules must be equal";
    }
    return Galois(this->value + other.value, this->mod);
}

Galois Galois::operator- (const Galois& other)
{
    if (this->mod != other.mod)
    {
        throw "Modules must be equal";
    }

    Galois res;
    if (this->value >= other.value)
    {
        res = Galois(this->value - other.value, this->mod);
    }
    else
    {
        res = Galois(mod - other.value + this->value, this->mod);
    }
    return res;
}

Galois Galois::operator- ()
{
    return Galois((this->mod) - (this->value), this->mod);
}

Galois Galois::operator* (const Galois& other)
{
    if (this->mod != other.mod)
    {
        throw "Modules must be equal";
    }

    return Galois((this->value) * other.value, this->mod);
}

Galois Galois::operator* (Galois& other)
{
    if (this->mod != other.mod)
    {
        throw "Modules must be equal";
    }

    return Galois((this->value) * other.value, this->mod);
}

Galois Galois::operator* (int_fast64_t other)
{
    return Galois(other * this->value, this->mod);
}

Galois Galois::inverse()
{
    if (!isprime(this->mod))
    {
        throw "mod must be prime";
    }

    if (this->value == 0)
    {
        throw "value must be nonzero";
    }

    int_fast64_t t = 0, t1 = 1, r = this->mod, r1 = this->value, t_tmp, r_tmp, q;

    while (r1 != 0)
    {
        q = r / r1;

        t_tmp = t;
        t = t1;
        t1 = t_tmp - q * t1;

        r_tmp = r;
        r = r1;
        r1 = r_tmp - q * r1;
    }

    if (t < 0)
    {
        t += this->mod;
    }
    return Galois(t, this->mod);
}

Galois Galois::operator/ (const Galois& other)
{
    Galois a(other);
    return (*this) * a.inverse();
}

Galois Galois::pow(int_fast64_t other)
{
    Galois res = Galois(this->mod == 1 ? 0 : 1, this->mod), a = *this;
    if (other < 0)
    {
        a = a.inverse();
        other = -other;
    }
    while (other > 0)
    {
        if (other & 1)
            res = res * a;
        other = other >> 1;
        a = a * a;
    }
    return res;
}

Galois Galois::operator += (const Galois other)
{
    *this = *this + other;
    return *this;
}

Galois Galois::operator -= (const Galois other)
{
    *this = *this - other;
    return *this;
}

Galois Galois::operator *= (const Galois other)
{
    *this = *this * other;
    return *this;
}

Galois Galois::operator /= (Galois other)
{
    *this = *this / other;
    return *this;
}

const int_fast64_t Galois::get_value()
{
    return this->value;
}

const int_fast64_t Galois::get_mod()
{
    return this->mod;
}

