#include <iostream>
#include "fraction.hpp"

int main()
{
    Fraction f1 { 3, 4 };
    Fraction f2 { 1, 2 };

    std::cout << "f1 = ";
    f1.display();
    std::cout << " f2 = ";
    f2.display();
    std::cout << std::endl;

    Fraction f3 { f1 + f2 };

    std::cout << "add(f1, f2) = ";
    f3.display();

    std::cout << std::endl << "sub(f1, f2) = ";
    (f1 - f2).display();

    std::cout << std::endl << "mul(f1, f2) = ";
    (f1 * f2).display();

    std::cout << std::endl << "div(f1, f2) = ";
    (f1 / f2).display();

    std::cout << std::endl << "add(1/6, 2/6) = ";
    Fraction f4 {1, 6};
    Fraction f5 {2, 6};
    (f4 + f5).display();

    Fraction f11 { 1, 2 };
    Fraction f12 { 1, 3 };
    Fraction f13 {f11 + f12};
    f13.display();
    f13 += f11;
    f13.display();
    f13 *= f12;
    f13.display();
    f13 /= f11;
    f13.display();
    f13 -= f12;
    f3.display();
    if (f11 < f12) {
        std::cout << "f1 < f2" << std::endl;
    }
    if (f11 != f12) {
        std::cout << "f1 != f2" << std::endl;
    }
    if (f11 == f12) {
        std::cout << "f1 == f2" << std::endl;
    }
    if (f11 >= f12) {
        std::cout << "f1 >= f2" << std::endl;
    }
    if (f11 > f12) {
        std::cout << "f1 > f2" << std::endl;
    }
    if (f11 <= f12) {
        std::cout << "f1 <= f2" << std::endl;
    }
    float f = f11;
    std::cout << f << std::endl; // 0.5

    Fraction f16 = f11 + 2;
    f16.display();
    Fraction f17 = f11 - 2;
    f17.display();
    Fraction f18 = f11 * 2;
    f18.display();
    Fraction f19 = f11 / 2;
    f19.display();

    Fraction f20 = 2 + f11;
    f20.display();
    Fraction f21 = 2 - f11;
    f21.display();
    Fraction f22 = 2 * f11;
    f22.display();
    Fraction f23 = 2 / f11;
    f23.display();

    float f24 = to_float(f11);
    std::cout << f24 << std::endl; // 0.5

    return 0;
}
