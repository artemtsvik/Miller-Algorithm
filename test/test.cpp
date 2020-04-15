#include <iostream>
#include <cstdint>
#include <cmath>
#include <vector>
#include <string>
#include <unordered_map>
#include "modular_arithmetic.hpp"
#include "elliptic_curve.hpp"
#include "poly_and_ratio.hpp"
#include "calc_lines.hpp"


using std::vector;
using std::string;
using std::unordered_map;

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
        << "a1 * a2 = " << (a1 * a2).get_value() << std::endl
        << "a1 / a2 = " << (a1 / a2).get_value() << std::endl
        << "a1 ^ (-1) = " << a1.inverse().get_value() << std::endl
        << "a1 ^ 2 = " << a1.pow(2).get_value() << std::endl
        << "a1 ^ (-2) = " << a1.pow(-2).get_value() << std::endl
        << "a1 ^ 0 = " << a1.pow(0).get_value() << std::endl;

    std::cout << std::endl << std::endl << "-- test modular_arithmetic.cpp --" << std::endl << std::endl;

    EllipticCurve E = EllipticCurve(0, 2, 7);
    std::cout << "E is elliptic curve y^2 = x^3 + 2 over Z_7" << std::endl;
    
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

    
    std::cout << std::endl << std::endl << "-- test poly_and_ratio.cpp --" << std::endl << std::endl;

    unordered_map<string, Galois> data1, data2;

    data1["0, 0"] = Galois(1, 5);
    data1["0, 10"] = Galois(1, 5);
    data1["10, 0"] = Galois(1, 5);

    data2["0, 0"] = Galois(4, 5);
    data2["1, 0"] = Galois(2, 5);
    data2["0, 1"] = Galois(3, 5);
    data2["1, 1"] = Galois(3, 5);
    data2["2, 1"] = Galois(1, 5);

    Poly p1 = Poly(data1, 5), p2 = Poly(data2, 5);
    std::cout << "P1 = " << p1.get_str() << std::endl
        << "P2 = " << p2.get_str() << std::endl
        << "P1 and P2 are over Z_5" << std::endl << std::endl;

    Galois a = Galois(1, 5), b = Galois(4, 5);

    std::cout << "P1 + P2 = " << (p1 + p2).get_str() << std::endl
        << "P1 * P2 = " << (p1 * p2).get_str() << std::endl
        << "P1(1, 4) = " << p1.value(a, b).get_value() << std::endl
        << "P2(1, 4) = " << p2.value(a, b).get_value() << std::endl 
        << std::endl;

    Ratio r1 = Ratio(p1, p2);
    std::cout << "R1 = P1 / P2" << std::endl
        << "R1 = " << r1.get_str() << std::endl
        << "R1(1, 4) = " << r1.value(a, b).get_value() << std::endl
        << "R1 * R1 = " << (r1 * r1).get_str() << std::endl
        << "R1 * P1 = " << (r1 * p1).get_str() << std::endl;

    std::cout << std::endl << std::endl << "-- test calc_lines.cpp --" << std::endl << std::endl;

    EllipticCurve E1 = EllipticCurve(0, 11, 31);
    Galois x = Galois(24, 31), y = Galois(28, 31), c = Galois(6, 31);
    Point P1 = Point(x, y);
    Poly t = calc_tangent(P1, E1);
    std::cout << "E is elliptic curve y^2 = x^3 + 11 over Z_31" << std::endl
        << "P = (24, 28)" << std::endl
        << "is P on curve: " << (E1.is_point_on_curve(P1) ? "YES" : "NO") << std::endl
        << "tangent to E at P: " << (t * c.inverse()).get_str() << std::endl;

    system("pause");
    return 0;
}