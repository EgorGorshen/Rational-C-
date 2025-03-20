#include <cstdlib>  // exit
#include <iostream>
#include <stdexcept>

#include "rational.h"

// WARNING: тесты написаны при помощи chatgpt

// Вспомогательная функция для проверки соответствия ожидаемых числителя и
// знаменателя
void checkRational(const Rational& r, int expectedNum, int expectedDen,
                   const char* testName) {
    if (r.GetNumerator() != expectedNum || r.GetDenominator() != expectedDen) {
        std::cerr << "Test FAILED [" << testName << "]: "
                  << "expected (" << expectedNum << "/" << expectedDen
                  << ") but got (" << r.GetNumerator() << "/"
                  << r.GetDenominator() << ")" << std::endl;
        std::exit(1);
    }
}

// Вспомогательная функция для проверки булевых значений
void checkBool(bool value, bool expected, const char* testName) {
    if (value != expected) {
        std::cerr << "Test FAILED [" << testName << "]: "
                  << "expected " << (expected ? "true" : "false") << " but got "
                  << (value ? "true" : "false") << std::endl;
        std::exit(1);
    }
}

int main() {
    try {
        // 1) Тест конструктора по умолчанию
        {
            Rational r;
            checkRational(r, 0, 1, "Default constructor");
        }

        // 2) Тест конструктора с одним параметром
        {
            Rational r(5);
            checkRational(r, 5, 1, "Single-argument constructor");
        }

        // 3) Тест конструктора с двумя параметрами
        {
            Rational r(3, 6);
            // 3/6 должно упроститься до 1/2
            checkRational(r, 1, 2, "Two-argument constructor + normalize");
        }

        // 4) Тест исключения при передаче нулевого знаменателя
        {
            bool caught = false;
            try {
                Rational r(1, 0);
            } catch (const RationalDivisionByZero&) {
                caught = true;
            }
            checkBool(caught, true, "Exception on zero denominator");
        }

        // 5) Тест автоматической нормализации знака
        {
            Rational r(-4, -8);
            // -4 / -8 --> 4 / 8 --> 1 / 2
            checkRational(r, 1, 2, "Sign normalization");
        }

        // 6) Тест операторов Get/Set
        {
            Rational r;
            r.SetNumerator(10);
            r.SetDenominator(20);
            // 10/20 упростится до 1/2
            checkRational(r, 1, 2, "SetNumerator/SetDenominator + normalize");
        }

        // 7) Тест операторов +, -, *, /
        {
            Rational r1(1, 2);
            Rational r2(1, 3);

            Rational sum = r1 + r2;  // 1/2 + 1/3 = 3/6 + 2/6 = 5/6
            checkRational(sum, 5, 6, "Operator +");

            Rational diff = r1 - r2;  // 1/2 - 1/3 = 3/6 - 2/6 = 1/6
            checkRational(diff, 1, 6, "Operator -");

            Rational mul = r1 * r2;  // 1/2 * 1/3 = 1/6
            checkRational(mul, 1, 6, "Operator *");

            Rational div = r1 / r2;  // (1/2) / (1/3) = (1/2)*(3/1) = 3/2
            checkRational(div, 3, 2, "Operator /");
        }

        // 8) Тест операторов сравнения
        {
            Rational r1(1, 2);
            Rational r2(1, 2);
            Rational r3(3, 6);
            Rational r4(2, 3);

            checkBool(r1 == r2, true, "Operator ==");
            checkBool(r1 == r3, true, "Operator == (normalize check)");
            checkBool(r1 != r4, true, "Operator !=");
            checkBool(r4 > r1, true, "Operator >");
            checkBool(r1 < r4, true, "Operator <");
            checkBool(r1 >= r3, true, "Operator >=");
            checkBool(r1 <= r3, true, "Operator <=");
        }

        // 9) Тест унарных + и -
        {
            Rational r1(1, 2);
            Rational plus = +r1;  // +1/2 = 1/2
            checkRational(plus, 1, 2, "Unary +");

            Rational minus = -r1;  // -(1/2) = -1/2
            checkRational(minus, -1, 2, "Unary -");
        }

        // 10) Тест операторов инкремента и декремента
        {
            Rational r(1, 2);        // 1/2
            Rational postInc = r++;  // postInc = 1/2, r = 3/2
            checkRational(postInc, 1, 2, "Post-increment (old value)");
            checkRational(r, 3, 2, "Post-increment (new value)");

            Rational preInc = ++r;  // ++r = 5/2
            checkRational(preInc, 5, 2, "Pre-increment (returned value)");
            checkRational(r, 5, 2, "Pre-increment (object value)");

            Rational postDec = r--;  // postDec = 5/2, r = 3/2
            checkRational(postDec, 5, 2, "Post-decrement (old value)");
            checkRational(r, 3, 2, "Post-decrement (new value)");

            Rational preDec = --r;  // --r = 1/2
            checkRational(preDec, 1, 2, "Pre-decrement (returned value)");
            checkRational(r, 1, 2, "Pre-decrement (object value)");
        }

        // 11) Тесты ввода/вывода (простая проверка)
        {
            // Попробуем вывести и тут же считать
            Rational r1(2, 4);             // это 1/2
            std::cout << r1 << std::endl;  // ожидаем "1/2" в консоль

            // Для реального автотестирования обычно мы бы проверяли строку
            // вывода отдельно; но здесь, без дополнительных библиотек, просто
            // продемонстрируем ввод: Пример ввода: "3/4" Чтобы проверить,
            // раскомментируйте и введите вручную во время запуска: Rational r2;
            // std::cin >> r2;
            // checkRational(r2, 3, 4, "Operator >> (manual check)");

            // Так как полноценный автоматизированный тест без сторонних
            // библиотек для потокового ввода-вывода сложнее, оставляем это как
            // демонстрацию.
        }

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
