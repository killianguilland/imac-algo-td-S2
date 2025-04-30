#include "fraction.hpp"
#include "utils.hpp"

#include <iostream>


// Affichage

std::ostream& operator<<(std::ostream& os, Fraction const& f) {
    return os << f.numerator << "/" << f.denominator;
}

void Fraction::display() {
   std::cout << *this << std::endl;
}


// Opérations

Fraction operator+(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator + f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    });
}

Fraction operator-(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator - f2.numerator * f1.denominator,
        f1.denominator * f2.denominator
    });
}

Fraction operator*(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.numerator,
        f1.denominator * f2.denominator
    });
}

Fraction operator/(Fraction const& f1, Fraction const& f2) {
    return simplify({
        f1.numerator * f2.denominator,
        f1.denominator * f2.numerator
    });
}


// Comparaisons

bool operator==(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator == f2.numerator * f1.denominator;
}

bool operator!=(Fraction const& f1, Fraction const& f2) {
    return !(f1 == f2);
}

bool operator<(Fraction const& f1, Fraction const& f2) {
    return f1.numerator * f2.denominator < f2.numerator * f1.denominator;
}

bool operator>(Fraction const& f1, Fraction const& f2) {
    return !(f1 < f2);
}

bool operator<=(Fraction const& f1, Fraction const& f2) {
    return f1 < f2 || f1 == f2;
}

bool operator>=(Fraction const& f1, Fraction const& f2) {
    return f1 > f2 || f1 == f2;
}


// Opérations "directes"

void operator+=(Fraction& f1, Fraction const& f2) {
    f1 = f1 + f2;
}

void operator-=(Fraction& f1, Fraction const& f2) {
    f1 = f1 - f2;
}

void operator*=(Fraction& f1, Fraction const& f2) {
    f1 = f1 * f2;
}

void operator/=(Fraction& f1, Fraction const& f2) {
    f1 = f1 / f2;
}


// Conversion

float to_float(Fraction const& f) {
    return static_cast<float>(f.numerator) / f.denominator;
}

Fraction::operator float() const {
    return to_float(*this);
}


// Aller + loin

Fraction operator+(Fraction const& f, int const i) {
    Fraction int_fraction {i, 1};
    return f + int_fraction;
}
Fraction operator+(int const i, Fraction const& f) {
    return f + i;
}

Fraction operator-(Fraction const& f, int const i) {
    Fraction int_fraction {i, 1};
    return f - int_fraction;
}
Fraction operator-(int const i, Fraction const& f) { 
    // L'opération n'est pas commutative donc je n'appelle pas la fonction précédente
    Fraction int_fraction {i, 1};
    return int_fraction - f;
}

Fraction operator*(Fraction const& f, int const i) {
    Fraction int_fraction {i, 1};
    return f * int_fraction;
}
Fraction operator*(int const i, Fraction const& f) {
    return f * i;
}

Fraction operator/(Fraction const& f, int const i) {
    Fraction int_fraction {i, 1};
    return f / int_fraction;
}
Fraction operator/(int const i, Fraction const& f) {
    // L'opération n'est pas commutative donc je n'appelle pas la fonction précédente
    Fraction int_fraction {i, 1};
    return int_fraction / f;
}


//  Aller + loin (suite)

void Fraction::abs() {
    numerator = std::abs(numerator);
    denominator = std::abs(denominator);
    simplify(*this);
}

void Fraction::ceil() {
    numerator = static_cast<int>(std::ceil(static_cast<double>(numerator) / denominator));
    denominator = 1;
    simplify(*this);
}

void Fraction::floor() {
    numerator = static_cast<int>(std::floor(static_cast<double>(numerator) / denominator));
    denominator = 1;
    simplify(*this);
}

void Fraction::round() {
    numerator = static_cast<int>(std::round(static_cast<double>(numerator) / denominator));
    denominator = 1;
    simplify(*this);
}