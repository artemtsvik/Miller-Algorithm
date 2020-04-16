# Miller-Algorithm

modular_arithmetic
- uint_fast64_t bsqrt(uint_fast64_t a) знаходить цілу частину від кореня цілого числа
- bool isprime(uint_fast64_t a) перевіряє чи є дане натуральне число a простим
- class Galois - кільце лишків за модулем mod

poly_and_ratio
- class Poly - Клас поліном, в якому data - хеш-таблиця коефіцієнтів Galois, в якій ключ має мати вигляд "m, k", що відповідає моному x^m * y^k, де k, m є невід'ємними цілими числами. Параметр mod визначає якому кільцю лишків мають належати коефіцієнти.
- class Ratio - Клас раціональна функція. numerator, denominator - поліноми, які мають коефіцієнти з одного кільця лишків

elliptic_curve
- class Point Точка, координати якої x та y належать деякому кільцю лишків. Якщо булева змінна is_infinity = true, то це нескінченно віддалена точка
- class EllipticCurve Еліптична крива, яка має вигляд y^2 = x^3 + a*x + b. Для коректної роботи методів double_point, add_points, sub_points параметр q, який визначає якому кільцю лишків мають належати координати точок кривої, має бути простим

calc_lines
- Poly calc_line(Point& P, Point& Q, EllipticCurve& E) обчислює січну, яка проходить через точки P та Q, які належать еліптичній кривій E
- Poly calc_tangent(Point& P, EllipticCurve& E) Обчислює дотичну до еліптичної кривої E в точці P

main
- Ratio miller_algorithm(EllipticCurve& E, Point& P, uint_fast32_t r) - алгоритм Міллера з розділу 4.3
