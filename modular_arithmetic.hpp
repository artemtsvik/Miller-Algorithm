#include <cstdint>

#ifndef MODULAR_ARITHMETIC_H
#define MODULAR_ARITHMETIC_H

uint_fast64_t bsqrt(uint_fast64_t a);

bool isprime(uint_fast64_t a);

class Galois
{
private:
    int_fast64_t value;
    int_fast64_t mod;

public:
    Galois(int_fast64_t x, int_fast64_t n);
    Galois();

    bool operator == (const Galois& other);

    bool operator == (Galois& other);

    bool operator == (int_fast64_t other);

    bool operator != (const Galois& other);

    bool operator != (int_fast64_t other);

    Galois& operator = (const Galois& other);

    Galois& operator = (int_fast64_t other);

    Galois operator+ (const Galois& other);

    Galois operator- (const Galois& other);

    Galois operator- ();

    Galois operator* (const Galois& other);

    Galois operator* (int_fast64_t other);

    Galois inverse();

    Galois operator/ (const Galois& other);

    Galois pow(int_fast64_t other);

    Galois operator += (const Galois other);

    Galois operator -= (const Galois other);

    Galois operator *= (const Galois other);

    Galois operator /= (const Galois other);

    const int_fast64_t get_mod();

    const int_fast64_t get_value();
};

#endif