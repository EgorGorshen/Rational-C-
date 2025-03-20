#pragma once

#include <iostream>
#include <stdexcept>

class RationalDivisionByZero : public std::exception {};

class Rational {
   public:
    // NOTE: done
    Rational() : numerator_(0), denominator_(1) {
    }

    Rational(int numerator) : numerator_(numerator), denominator_(1) {
    }

    Rational(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            throw RationalDivisionByZero{};
        }
        if (denominator_ < 0) {
            denominator_ *= -1;
            numerator_ *= -1;
        }
        Normalize();
    };

    int GetNumerator() const;
    int GetDenominator() const;

    void SetNumerator(int numerator);
    void SetDenominator(int denominator);

    Rational& operator+=(const Rational& obj);
    Rational& operator-=(const Rational& obj);
    Rational& operator*=(const Rational& obj);
    Rational& operator/=(const Rational& obj);

    Rational operator+() const;
    Rational operator-() const;

    Rational& operator++();
    Rational& operator--();
    Rational operator++(int);
    Rational operator--(int);

    friend Rational operator+(Rational obj1, const Rational& obj2) {
        obj1 += obj2;
        return obj1;
    }

    friend Rational operator-(Rational obj1, const Rational& obj2) {
        obj1 -= obj2;
        return obj1;
    }

    friend Rational operator*(Rational obj1, const Rational& obj2) {
        obj1 *= obj2;
        return obj1;
    }

    friend Rational operator/(Rational obj1, const Rational& obj2) {
        obj1 /= obj2;
        return obj1;
    }

    friend bool operator==(const Rational& obj1, const Rational& obj2);
    friend bool operator!=(const Rational& obj1, const Rational& obj2);
    friend bool operator<(const Rational& obj1, const Rational& obj2);
    friend bool operator>(const Rational& obj1, const Rational& obj2);
    friend bool operator<=(const Rational& obj1, const Rational& obj2);
    friend bool operator>=(const Rational& obj1, const Rational& obj2);

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);

   private:
    int numerator_;
    int denominator_;

    void Normalize();
};
