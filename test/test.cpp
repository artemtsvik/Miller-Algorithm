#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include "modular_arithmetic.hpp"
#include "elliptic_curve.hpp"


using std::vector;


int main()
{
    std::cout << "-- test modular_arithmetic.cpp --" << std::endl;

    std::cout << "bsqrt(169) = " << sqrt(169) << std::endl
        << "bsqrt(0) = " << sqrt(0) << std::endl
        << "bsqrt(1) = " << sqrt(1) << std::endl << std::endl;

    vector<uint_fast64_t> testsp = { 2, 3, 4, 5, 7, 37, 169, 10000000000001, 2017 };
    for (uint_fast64_t el : testsp)
    {
        std::cout << "is " << el << " prime: " << (isprime(el) ? "YES" : "NO") << std::endl;
    }
    std::cout << std::endl;
    
    Galois a1 = Galois(2, 7), a2 = Galois(3, 7);
    std::cout << "a1 = 2, a2 = 3 in Z_7" << std::endl
        << "2 * a1 = " << (a1 * 2).get_value() << std::endl
        << "-a1 = " << (-a1).get_value() << std::endl
        << "(-2) * a1 = " << (a1 * -2).get_value() << std::endl
        << "a1 + a2 = " << (a1 + a2).get_value() << std::endl
        << "a1 - a2 = " << (a1 - a2).get_value() << std::endl
        << "a1 ^ (-1) = " << a1.inverse().get_value() << std::endl
        << "a1 ^ 2 = " << a1.pow(2).get_value() << std::endl
        << "a1 ^ (-2) = " << a1.pow(-2).get_value() << std::endl
        << "a1 ^ 0 = " << a1.pow(0).get_value() << std::endl;
    std::cout << std::endl;

    std::cout << "-- test modular_arithmetic.cpp --" << std::endl;

    EllipticCurve E = EllipticCurve(0, 2, 7);
    std::cout << "E is elliptic curve y^3 = x^3 + 2 over Z_7" << std::endl;
    
    Point P = Point(Galois(5, 7), Galois(1, 7)), Q = Point(Galois(6, 7), Galois(1, 7)), T = Point(Galois(5, 7), Galois(6, 7)),
        R1 = E.add_points(P, Q), R2 = E.add_points(P, P), R3 = E.add_points(T, P), R4 = E.add_points(P, R3),
        R5 = E.add_points(R3, P), R6 = -Q, R7 = E.sub_points(T, P);

    std::cout << "P = (5, 1), Q = (6, 1), T = (5, 6) on E" << std::endl;

    std::cout << "P + Q = (" << R1.get_x().get_value() << ", " << R1.get_y().get_value() << ")" << std::endl
        << "2 * P = (" << R2.get_x().get_value() << ", " << R2.get_y().get_value() << ")" << std::endl
        << "T + P = (" << (R3.isinfty() ? "infty" : "nonifty") << ")" << std::endl
        << "P + (infty) = (" << R4.get_x().get_value() << ", " << R4.get_y().get_value() << ")" << std::endl
        << "(infty) + P = (" << R5.get_x().get_value() << ", " << R5.get_y().get_value() << ")" << std::endl
        << "-Q = (" << R6.get_x().get_value() << ", " << R6.get_y().get_value() << ")" << std::endl
        << "is -Q on E:" << (E.is_point_on_curve(R6) ? "YES" : "NO") << std::endl
        << "is P + Q on E:" << (E.is_point_on_curve(R1) ? "YES" : "NO") << std::endl
        << "is 2 * P on E:" << (E.is_point_on_curve(R2) ? "YES" : "NO") << std::endl
        << "is T + P on E:" << (E.is_point_on_curve(R3) ? "YES" : "NO") << std::endl
        << "is T - P on E:" << (E.is_point_on_curve(R7) ? "YES" : "NO") << std::endl;

    system("pause");
    return 0;
}