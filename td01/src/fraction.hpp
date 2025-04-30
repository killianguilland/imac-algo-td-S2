#pragma once

struct Fraction {
    int numerator { 0 };
    int denominator { 1 };

    void display();

    operator float() const;

    void abs();
    void ceil();
    void floor();
    void round();
};

Fraction operator+(Fraction const& f1, Fraction const& f2);
Fraction operator-(Fraction const& f1, Fraction const& f2);
Fraction operator*(Fraction const& f1, Fraction const& f2);
Fraction operator/(Fraction const& f1, Fraction const& f2);
bool operator==(Fraction const& f1, Fraction const& f2);
bool operator!=(Fraction const& f1, Fraction const& f2);
bool operator<(Fraction const& f1, Fraction const& f2);
bool operator>(Fraction const& f1, Fraction const& f2);
bool operator<=(Fraction const& f1, Fraction const& f2);
bool operator>=(Fraction const& f1, Fraction const& f2);
void operator+=(Fraction& f1, Fraction const& f2);
void operator-=(Fraction& f1, Fraction const& f2);
void operator*=(Fraction& f1, Fraction const& f2);
void operator/=(Fraction& f1, Fraction const& f2);
float to_float(Fraction const& f);
Fraction operator+(Fraction const& f, int const i);
Fraction operator-(Fraction const& f, int const i);
Fraction operator*(Fraction const& f, int const i);
Fraction operator/(Fraction const& f, int const i);
Fraction operator+(int const i, Fraction const& f);
Fraction operator-(int const i, Fraction const& f);
Fraction operator*(int const i, Fraction const& f);
Fraction operator/(int const i, Fraction const& f);