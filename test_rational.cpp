#include <cstdlib>  // exit
#include <iostream>
#include <sstream>  // для stringstream
#include <stdexcept>

#include "rational.h"

// WARNING: тесты написаны chatgpt

// Вспомогательная функция для проверки (expected == actual).
// При несоответствии прерываем тесты и выводим сообщение.
void checkEqualInt(int expected, int actual, const char* testName) {
    if (expected != actual) {
        std::cerr << "Test FAILED [" << testName << "]: expected " << expected
                  << ", got " << actual << std::endl;
        std::exit(1);
    }
}

void checkEqualBool(bool expected, bool actual, const char* testName) {
    if (expected != actual) {
        std::cerr << "Test FAILED [" << testName << "]: expected "
                  << (expected ? "true" : "false") << ", got "
                  << (actual ? "true" : "false") << std::endl;
        std::exit(1);
    }
}

void checkRational(const Rational& r, int expectedNum, int expectedDen,
                   const char* testName) {
    if (r.GetNumerator() != expectedNum || r.GetDenominator() != expectedDen) {
        std::cerr << "Test FAILED [" << testName << "]: expected ("
                  << expectedNum << "/" << expectedDen << "), got ("
                  << r.GetNumerator() << "/" << r.GetDenominator() << ")"
                  << std::endl;
        std::exit(1);
    }
}

void checkStringEqual(const std::string& expected, const std::string& actual,
                      const char* testName) {
    if (expected != actual) {
        std::cerr << "Test FAILED [" << testName << "]: expected \"" << expected
                  << "\", got \"" << actual << "\"" << std::endl;
        std::exit(1);
    }
}

int main() {
    try {
        //--------------------------------------------------------------------------
        // 1) Конструктор по умолчанию: 0/1
        {
            Rational r;
            checkRational(r, 0, 1, "Default constructor");
        }

        //--------------------------------------------------------------------------
        // 2) Неявный конструктор из целого (Rational x = 5; // NOLINT)
        {
            Rational r = 5;  // NOLINT
            checkRational(r, 5, 1, "Implicit int constructor");
        }

        //--------------------------------------------------------------------------
        // 3) Конструктор от двух целых чисел с нормализацией
        //    Проверяем сократимость и вынос знака в числитель
        {
            Rational r1(3, 6);  // должно упроститься до 1/2
            checkRational(r1, 1, 2, "Constructor(3,6)");

            Rational r2(14, -6);  // -7/3
            checkRational(r2, -7, 3, "Constructor(14, -6)");

            Rational r3(-4, -8);  // => 4/8 => 1/2
            checkRational(r3, 1, 2, "Constructor(-4, -8)");
        }

        //--------------------------------------------------------------------------
        // 4) Методы GetNumerator() и GetDenominator()
        {
            Rational r(5, 7);
            checkEqualInt(5, r.GetNumerator(), "GetNumerator()");
            checkEqualInt(7, r.GetDenominator(), "GetDenominator()");
        }

        //--------------------------------------------------------------------------
        // 5) Методы SetNumerator() и SetDenominator().
        //    Проверяем сократимость, знак и исключение при denominator=0
        {
            Rational r;
            r.SetNumerator(10);
            r.SetDenominator(20);  // 10/20 -> 1/2
            checkRational(r, 1, 2, "SetNumerator/SetDenominator -> 1/2");

            bool caught = false;
            try {
                r.SetDenominator(0);
            } catch (const RationalDivisionByZero&) {
                caught = true;
            }
            checkEqualBool(true, caught, "SetDenominator(0) -> throw");
        }

        //--------------------------------------------------------------------------
        // 6) Бинарные арифметические операции (+, -, *, /) и их присваивающие
        // версии
        {
            Rational r1(1, 2);  // 1/2
            Rational r2(1, 3);  // 1/3

            // +, -
            checkRational(r1 + r2, 5, 6, "1/2 + 1/3 = 5/6");
            checkRational(r1 - r2, 1, 6, "1/2 - 1/3 = 1/6");

            // *, /
            checkRational(r1 * r2, 1, 6, "1/2 * 1/3 = 1/6");
            checkRational(r1 / r2, 3, 2, "1/2 / 1/3 = 3/2");

            // +=, -=, *=, /=
            Rational rr(2, 4);  // упрощается до 1/2
            rr += Rational(1, 2);
            // 1/2 + 1/2 = 1/1
            checkRational(rr, 1, 1, "operator +=");

            rr = Rational(3, 4);
            rr -= Rational(1, 2);
            // 3/4 - 1/2 = 3/4 - 2/4 = 1/4
            checkRational(rr, 1, 4, "operator -=");

            rr = Rational(2, 3);
            rr *= Rational(3, 4);
            // 2/3 * 3/4 = 6/12 = 1/2
            checkRational(rr, 1, 2, "operator *=");

            rr = Rational(4, 5);
            rr /= Rational(2, 5);
            // (4/5) / (2/5) = (4/5)*(5/2) = 20/10 = 2/1
            checkRational(rr, 2, 1, "operator /=");

            // Проверка исключения при делении на 0
            bool caughtDivZero = false;
            try {
                Rational a(1, 2);
                Rational b(0, 1);
                a /= b;  // должно бросать исключение RationalDivisionByZero
            } catch (const RationalDivisionByZero&) {
                caughtDivZero = true;
            }
            checkEqualBool(true, caughtDivZero, "operator /= 0 -> throw");
        }

        //--------------------------------------------------------------------------
        // 7) Унарные операции +, -
        {
            Rational r(1, 2);
            Rational plus_r = +r;   // должно быть таким же, 1/2
            Rational minus_r = -r;  // -1/2
            checkRational(plus_r, 1, 2, "Unary +");
            checkRational(minus_r, -1, 2, "Unary -");
        }

        //--------------------------------------------------------------------------
        // 8) Префиксные и постфиксные инкременты/декременты
        {
            // Проверяем пошагово, чтобы отследить корректные значения:
            Rational r(1, 2);  // 1/2

            // Постфиксный инкремент
            Rational rPostInc = r++;
            // rPostInc должно быть 1/2, а r станет 3/2
            checkRational(rPostInc, 1, 2, "r++ (old value)");
            checkRational(r, 3, 2, "r++ (new value)");

            // Префиксный инкремент
            Rational rPreInc = ++r;
            // r должно стать 5/2, и rPreInc тоже 5/2
            checkRational(r, 5, 2, "++r (object after)");
            checkRational(rPreInc, 5, 2, "++r (returned value)");

            // Постфиксный декремент
            Rational rPostDec = r--;
            // rPostDec = 5/2, а r = 3/2
            checkRational(rPostDec, 5, 2, "r-- (old value)");
            checkRational(r, 3, 2, "r-- (new value)");

            // Префиксный декремент
            Rational rPreDec = --r;
            // rPreDec = 1/2, r тоже 1/2
            checkRational(rPreDec, 1, 2, "--r (returned value)");
            checkRational(r, 1, 2, "--r (object after)");
        }

        //--------------------------------------------------------------------------
        // 9) Операции сравнения
        {
            Rational r1(1, 2);
            Rational r2(1, 2);
            Rational r3(3, 6);  // упрощается до 1/2
            Rational r4(2, 3);

            checkEqualBool(true, r1 == r2, "operator== (same fraction)");
            checkEqualBool(true, r1 == r3, "operator== (normalize check)");
            checkEqualBool(false, r1 == r4, "operator== (different)");

            checkEqualBool(true, r1 != r4, "operator!= (different)");
            checkEqualBool(false, r1 != r3, "operator!= (normalize same)");

            checkEqualBool(true, r1 < r4, "1/2 < 2/3");
            checkEqualBool(false, r4 < r1, "2/3 < 1/2 ? false");

            checkEqualBool(true, r4 > r1, "2/3 > 1/2");
            checkEqualBool(false, r1 > r2, "1/2 > 1/2 ? false");

            checkEqualBool(true, r1 <= r2, "1/2 <= 1/2 ? true");
            checkEqualBool(true, r1 <= r4, "1/2 <= 2/3 ? true");
            checkEqualBool(false, r4 <= r1, "2/3 <= 1/2 ? false");

            checkEqualBool(true, r4 >= r1, "2/3 >= 1/2 ? true");
            checkEqualBool(true, r1 >= r3, "1/2 >= 1/2 ? true");
            checkEqualBool(false, r1 >= r4, "1/2 >= 2/3 ? false");
        }

        //--------------------------------------------------------------------------
        // 10) Операции ввода/вывода
        //     - Вывод: если знаменатель = 1, выводим только числитель.
        //     - Нормализуем отрицательный знаменатель и сокращаем дробь при
        //     вводе.
        {
            // 10.1) Проверяем вывод в виде "числитель/знаменатель" или просто
            // "числитель"
            {
                std::ostringstream oss;
                Rational r1(5, 1);
                oss << r1;  // ожидаем "5" (без /1)
                checkStringEqual("5", oss.str(), "ostream << (den=1)");

                oss.str("");
                oss.clear();
                Rational r2(3, 2);
                oss << r2;  // ожидаем "3/2"
                checkStringEqual("3/2", oss.str(), "ostream << (3/2)");
            }

            // 10.2) Проверяем ввод (istream >>) с нормализацией
            {
                {
                    std::istringstream iss("14/-6");
                    Rational r;
                    iss >> r;  // должно стать -7/3
                    checkRational(r, -7, 3, "istream >> (14/-6)");
                }
                {
                    // Если знаменатель = 1, то может быть ввод просто "5", но
                    // по условию формально формат <числитель>/<знаменатель>.
                    // Однако давайте протестируем и вариант без знака дроби:
                    // В идеале надо обрабатывать оба случая, но если в вашем
                    // решении ожидается строго <num>/<den>, то этот тест можете
                    // пропустить.
                    //
                    // Пример (на усмотрение автора класса):
                    std::istringstream iss2("5");
                    Rational r2;
                    iss2 >> r2;  // ожидаем 5/1
                    checkRational(r2, 5, 1, "istream >> (5)");
                }
                {
                    // Ввод корректной дроби с сокращением
                    std::istringstream iss3("6/8");
                    Rational r3;
                    iss3 >> r3;  // 6/8 -> 3/4
                    checkRational(r3, 3, 4, "istream >> (6/8) => 3/4");
                }
            }
        }

        //--------------------------------------------------------------------------
        // 11) Проверяем работу с делением на 0 (установка 0 в знаменатель)
        {
            // Уже было частично выше, но добавим ещё один прямой тест:
            bool caught = false;
            try {
                Rational r(1, 0);  // конструктор должен бросить исключение
            } catch (const RationalDivisionByZero&) {
                caught = true;
            }
            checkEqualBool(true, caught, "Constructor(1,0) -> throw");
        }

        //--------------------------------------------------------------------------
        std::cout << "All tests PASSED successfully!" << std::endl;
        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Unknown exception caught!" << std::endl;
        return 1;
    }
}
