#include <iostream>
#include <string>
#include <sstream>
#include <numeric>
#include <cmath>

using namespace std;

int gcd(int a, int b) {
    return std::abs(std::gcd(a, b));
}

class Fraction {
private:
    int numerator;
    int denominator;

    void simplify() {
        if (denominator == 0) {
            cerr << "Помилка (simplify): Знаменник не може бути нулем." << endl;
            return;
        }
        if (numerator == 0) {
            denominator = 1;
            return;
        }
        int common_divisor = gcd(numerator, denominator);
        numerator /= common_divisor;
        denominator /= common_divisor;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Fraction(int num, int den) {
        if (den == 0) {
            cerr << "Помилка (конструктор): Знаменник не може бути нулем. Встановлено 1." << endl;
            den = 1;
        }
        numerator = num;
        denominator = den;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }

        // simplify();
    }

    string toString() {
        stringstream ss;
        int num_abs = abs(numerator);
        int den_abs = abs(denominator);

        if (numerator == 0) {
            return "0";
        }

        bool is_negative = numerator < 0;
        int whole_part = num_abs / den_abs;
        int remainder_num = num_abs % den_abs;

        if (is_negative) {
            ss << "-";
        }

        if (whole_part != 0) {
            ss << whole_part;
            if (remainder_num != 0) {
                ss << " ";
            }
        }

        if (remainder_num != 0) {
            ss << remainder_num << "/" << den_abs;
        }

        return ss.str();
    }

    double toDouble() {
        return static_cast<double>(numerator) / denominator;
    }
};

int main() {
    int num, den;
    string input_line;
    string num_str, den_str;
    size_t slash_pos;

    if (!getline(cin, input_line)) {
        cerr << "Помилка читання вхідних даних." << endl;
        return 1;
    }

    slash_pos = input_line.find('/');

    if (slash_pos == string::npos) {
        cerr << "Невірний формат введення. Очікується '[чисельник]/[знаменник]'." << endl;
        return 1;
    }

    num_str = input_line.substr(0, slash_pos);
    den_str = input_line.substr(slash_pos + 1);

    try {
        num = stoi(num_str);
        den = stoi(den_str);
    } catch (const std::invalid_argument& ia) {
        cerr << "Помилка конвертації: невірний формат числа у вхідних даних (" << ia.what() << ")" << endl;
        return 1;
    } catch (const std::out_of_range& oor) {
        cerr << "Помилка конвертації: число виходить за межі допустимого діапазону (" << oor.what() << ")" << endl;
        return 1;
    }

    if (den == 0) {
        cerr << "Помилка: Знаменник у введених даних не може бути нулем." << endl;
        return 1;
    }

    Fraction fraction(num, den);

    cout << fixed;
    cout.precision(2);

    cout << fraction.toString() << " is " << fraction.toDouble() << " in decimal" << endl;

    return 0;
}
