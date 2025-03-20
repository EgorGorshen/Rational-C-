#include "rational.h"

#include <numeric>
#include <string>

void Rational::Normalize() {
    if (denominator_ == 0) {
        throw RationalDivisionByZero{};
    }

    if (denominator_ < 0) {
        denominator_ *= -1;
        numerator_ *= -1;
    }

    int gcd_num = std::gcd(denominator_, numerator_);

    denominator_ /= gcd_num;
    numerator_ /= gcd_num;
}

int Rational::GetNumerator() const {
    return this->numerator_;
}

int Rational::GetDenominator() const {
    return this->denominator_;
}

void Rational::SetNumerator(int numerator) {
    numerator_ = numerator;
}
void Rational::SetDenominator(int denominator) {
    denominator_ = denominator;
    Normalize();
}

Rational& Rational::operator+=(const Rational& obj) {
    numerator_ = numerator_ * obj.denominator_ + obj.numerator_ * denominator_;
    denominator_ = denominator_ * obj.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator*=(const Rational& obj) {
    numerator_ = numerator_ * obj.numerator_;
    denominator_ = denominator_ * obj.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator-=(const Rational& obj) {
    numerator_ = numerator_ * obj.denominator_ - obj.numerator_ * denominator_;
    denominator_ = denominator_ * obj.denominator_;
    Normalize();
    return *this;
}

Rational& Rational::operator/=(const Rational& obj) {
    numerator_ *= obj.denominator_;
    denominator_ *= obj.numerator_;
    Normalize();
    return *this;
}

Rational Rational::operator+() const {
    return *this;
}

Rational Rational::operator-() const {
    return Rational(-numerator_, denominator_);
}

Rational& Rational::operator++() {
    *this += Rational(1);
    return *this;
}

Rational& Rational::operator--() {
    *this -= Rational(1);
    return *this;
}

Rational Rational::operator++(int) {
    Rational temp = *this;
    ++(*this);
    return temp;
}

Rational Rational::operator--(int) {
    Rational temp = *this;
    --(*this);
    return temp;
}

bool operator==(const Rational& obj1, const Rational& obj2) {
    return (obj1.GetNumerator() == obj2.GetNumerator()) &&
           (obj1.GetDenominator() == obj2.GetDenominator());
}

bool operator!=(const Rational& obj1, const Rational& obj2) {
    return (obj1.GetNumerator() != obj2.GetNumerator()) ||
           (obj1.GetDenominator() != obj2.GetDenominator());
}

bool operator<(const Rational& obj1, const Rational& obj2) {
    return obj1.GetNumerator() * obj2.GetDenominator() <
           obj2.GetNumerator() * obj1.GetDenominator();
}

bool operator>(const Rational& obj1, const Rational& obj2) {
    return obj2 < obj1;
}

bool operator<=(const Rational& obj1, const Rational& obj2) {
    return (obj1 < obj2) || (obj1 == obj2);
}

bool operator>=(const Rational& obj1, const Rational& obj2) {
    return obj2 <= obj1;
}

std::ostream& operator<<(std::ostream& os, const Rational& obj) {
    if (obj.denominator_ == 1) {
        os << obj.denominator_;
    } else {
        os << obj.numerator_ << '/' << obj.denominator_;
    }
    return os;
}

std::istream& operator>>(std::istream& is, Rational& r) {
    int numerator = 0;
    int denominator = 1;
    char slash;

    is >> numerator;

    if (is.peek() == '/') {
        is >> slash >> denominator;
    }

    Rational temp(numerator, denominator);
    r = temp;

    return is;
}
