#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <chrono>

using namespace std::chrono;

using namespace std;

class BigInteger {
private:
    string number;

public:
    BigInteger(const string& str) : number(str) {}

    void print() const {
        cout << number << endl;
    }

    bool operator>=(const BigInteger& other) const {
        return number.size() > other.number.size() || (number.size() == other.number.size() && number >= other.number);
    }


    BigInteger operator+(const BigInteger& other) const {
        string result;
        int carry = 0;
        int i = number.size() - 1;
        int j = other.number.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += number[i] - '0';
                i--;
            }
            if (j >= 0) {
                sum += other.number[j] - '0';
                j--;
            }

            result.push_back(sum % 10 + '0');
            carry = sum / 10;
        }

        reverse(result.begin(), result.end());
        return BigInteger(result);
    }

    BigInteger operator*(const BigInteger& other) const {
        int n = number.size();
        int m = other.number.size();
        string result(n + m, '0');

        for (int i = n - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = m - 1; j >= 0; --j) {
                int product = (number[i] - '0') * (other.number[j] - '0') +
                    (result[i + j + 1] - '0') + carry;

                carry = product / 10;
                result[i + j + 1] = (product % 10) + '0';
            }
            result[i] += carry;
        }

        // Remove leading zeros
        size_t pos = result.find_first_not_of('0');
        if (pos != string::npos)
            return BigInteger(result.substr(pos));

        return BigInteger("0");
    }

    BigInteger operator-(const BigInteger& other) const {
        string result;
        int borrow = 0;
        int i = number.size() - 1;
        int j = other.number.size() - 1;

        while (i >= 0 || j >= 0) {
            int diff = borrow;
            if (i >= 0) {
                diff += number[i] - '0';
                i--;
            }
            if (j >= 0) {
                diff -= other.number[j] - '0';
                j--;
            }

            if (diff < 0) {
                diff += 10;
                borrow = -1;
            }
            else {
                borrow = 0;
            }

            result.push_back(diff + '0');
        }

        // Remove leading zeros
        while (result.size() > 1 && result.back() == '0')
            result.pop_back();

        reverse(result.begin(), result.end());
        return BigInteger(result);
    }

    BigInteger operator/(const BigInteger& other) const {
        if (other.number == "0") {
            throw runtime_error("Division by zero");
        }

        BigInteger quotient("0");
        BigInteger remainder = *this;

        while (remainder >= other) {
            BigInteger subtracted = other;
            int count = 1;
            while (remainder >= (subtracted + subtracted)) {
                subtracted = subtracted + subtracted;
                count = count + count;
            }

            remainder = remainder - subtracted;
            quotient = quotient + BigInteger(to_string(count));
        }

        return quotient;
    }

    BigInteger operator%(const BigInteger& other) const {
        BigInteger quotient = *this / other;
        BigInteger result = *this - (other * quotient);
        return result;
    }

    BigInteger abs() const {
        if (number[0] == '-') {
            // Если число отрицательное, вернуть его модуль
            return BigInteger(number.substr(1));
        }
        else {
            // Если число положительное, вернуть его как есть
            return *this;
        }
    }

    // Добавим оператор вывода, чтобы легко выводить объекты BigInteger
    friend ostream& operator<<(ostream& os, const BigInteger& bi) {
        os << bi.number;
        return os;
    }
};

int main()
{
    auto start_time = chrono::steady_clock::now();
    delete new int(1);

    setlocale(LC_ALL, "rus");
    BigInteger num1("123456789012345");
    BigInteger num2("987654321987");

    cout << "num1: ";
    num1.print();

    cout << "num2: ";
    num2.print();

    BigInteger sum = num1 + num2;
    cout << "Сумма: ";
    sum.print();

    BigInteger product = num1 * num2;
    cout << "Произведение: ";
    product.print();

    BigInteger module = num1 % num2; // Вывод остатка
    cout << "Модуль от числа: ";
    module.print();



    auto end_time = chrono::steady_clock::now();
    auto elapsed_ns = chrono::duration_cast<chrono::nanoseconds>(end_time - start_time);
    cout << "Время работы программы = " << elapsed_ns.count() / 1000000 << " ms\n";

    return 0;
}
