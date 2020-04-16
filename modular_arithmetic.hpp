/**
* Реалізація кільця лишків
*/

#include <cstdint>

#ifndef MODULAR_ARITHMETIC_H
#define MODULAR_ARITHMETIC_H

/**
* Знаходить цілу частину від кореня цілого числа
*/
uint_fast64_t bsqrt(uint_fast64_t a);


/**
* Перевіряє чи є дане натуральне число a простим
*/
bool isprime(uint_fast64_t a);


/**
* Кільце лишків за модулем mod
*/
class Galois
{
private:
    int_fast64_t value;
    int_fast64_t mod;

public:
    /**
    * x та n мають бути не менше 0
    * value = x % n
    * mod = n
    */
    Galois(int_fast64_t x, int_fast64_t n);
    Galois();

    /**
    * Порівняння на рівність двох елементів з одного кільця
    */
    bool operator == (const Galois& other);

    bool operator == (Galois& other);

    /**
    * Порівняння на рівність з цілим числом по модулю mod
    */
    bool operator == (int_fast64_t other);

    bool operator != (const Galois& other);

    bool operator != (int_fast64_t other);

    Galois& operator = (const Galois& other);

    Galois& operator = (int_fast64_t other);

    Galois operator+ (const Galois& other);

    Galois operator- (const Galois& other);

    Galois operator- ();

    Galois operator* (const Galois& other);

    Galois operator* (Galois& other);

    Galois operator* (int_fast64_t other);

    /**
    * Знаходження оберненого елемента, якщо mod є простим числом. Інакше буде виключення.
    */
    Galois inverse();

    Galois operator/ (const Galois& other);

    /**
    * Піднесення до цілого степення other
    */
    Galois pow(int_fast64_t other);

    Galois operator += (const Galois other);

    Galois operator -= (const Galois other);

    Galois operator *= (const Galois other);

    Galois operator /= (const Galois other);

    const int_fast64_t get_mod();

    const int_fast64_t get_value();
};

#endif