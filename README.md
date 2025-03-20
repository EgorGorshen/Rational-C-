# cpp-dz

# Рациональное число с++ 

Данный проект содержит класс **Rational** и тесты, проверяющие его работоспособность. Класс реализует базовые операции над рациональными числами (числитель/знаменатель). Ниже описаны основные возможности, структура проекта и инструкции по запуску.


## class Rational

1. Обработка деления на 0:
   - Выбрасывается исключение `RationalDivisionByZero`.

2. Арифметические операции:
   - Бинарные `+`, `-`, `*`, `/` и присваивающие версии `+=`, `-=`, `*=`, `/=`.
   - Унарные `+`, `-`.

3. Инкремент/декремент:
   - Префиксные и постфиксные `++` и `--`.

4. Операторы сравнения:  
   `==`, `!=`, `<`, `<=`, `>`, `>=`.

5. Операции ввода/вывода:
   - Вывод (`operator<<`):  
     - Если знаменатель = 1, выводится только числитель.  
     - Иначе выводится в формате `числитель/знаменатель`.

   - Ввод (`operator>>`):  
     - Чтение в формате `числитель/знаменатель`.  
     - Автоматически нормализует знак (знаменатель становится положительным, а знак уходит в числитель).  
     - Допускается ввод с сокращаемой дробью; результат автоматически приводится к несократимой форме.

## Структура проекта

```
├── Makefile
├── rational.h
├── rational.cpp
├── test_rational.cpp
└── README.md
```

- rational.h  
  Объявление класса `Rational`, его полей, методов, а также класса-исключения `RationalDivisionByZero`.

- rational.cpp  
  Определение методов класса `Rational`, включая логику арифметических операций, операторов сравнения, ввода/вывода, сокращения дроби и т.д.

- test_rational.cpp  
  Набор тестов (без сторонних библиотек тестирования), которые проверяют корректность всех основных операций.  
  - При ошибке программа завершится с сообщением об ошибке.  
  - При успешном прохождении всех тестов выводится «All tests PASSED successfully!».

- Makefile  
  Содержит правила сборки и запуска тестов. Поддерживает различные платформы (Linux, Windows при использовании MSYS2/MinGW и т.п.).

## Сборка и запуск

Для сборки и запуска тестов используется стандартная утилита **make** и дефолтный компилятор C++ (обычно `c++` или `g++`):

1. Сборка  
   ```bash
   make
   ```
   В результате будет создан исполняемый файл `test_rational` (на Unix-подобных системах) или `test_rational.exe` (в Windows).

2. Запуск тестов  
   ```bash
   make run-tests
   ```
   Запустит программу с тестами. Если все проверки успешны, увидите сообщение:
   ```
   All tests PASSED successfully!
   ```
   При возникновении ошибок тест завершается с описанием того, что пошло не так.

3. Очистка  
   ```bash
   make clean
   ```
   Удалит сгенерированные объектные файлы и исполняемый файл/программу тестов.

## Пример использования

Ниже простой пример кода, иллюстрирующий использование `Rational`:

```cpp
#include <iostream>
#include "rational.h"

int main() {
    Rational a(1, 2);  // 1/2
    Rational b = 5;    // 5/1 
    Rational c(4, 8);  // сократится до 1/2

    std::cout << "a = " << a << std::endl;  // вывод: 1/2
    std::cout << "b = " << b << std::endl;  // вывод: 5
    std::cout << "c = " << c << std::endl;  // вывод: 1/2

    Rational sum = a + c;  // 1/2 + 1/2 = 1/1
    std::cout << "sum = " << sum << std::endl;  // вывод: 1

    return 0;
}
```

## Creator 

- Name: _Горшенков Егор Павлович_
- University: _Higher School of Economics_ "Bachelor's degree in Economics and Data Analysis (38.03.01, 01.03.02)"

