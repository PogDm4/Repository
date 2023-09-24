#include <iostream>

using namespace std;

int gcdExtended(int a, int b, int& x, int& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int gcd = gcdExtended(a, m, x, y);
    if (gcd != 1) {
        // обратный элемент не существует
        return -1;
    }
    else {
        // находим положительное значение обратного элемента
        return (x % m + m) % m;
    }
}


int main() {
    setlocale(LC_ALL, "Russian");
    int M;
    cout << "Введите значения M: ";
    cin >> M;

    int a, b;
    cout << "Введите два целых числа a и b: ";
    cin >> a >> b;

    // Сложение
    int addition = (a + b) % M;
    cout << "(a+b) mod M = " << addition << endl;

    // Вычитание
    int subtraction = (a - b + M) % M;
    cout << "(a-b) mod M = " << subtraction << endl;

    // Умножение
    int multiplication = (a * b) % M;
    cout << "(a*b) mod M = " << multiplication << endl;

    // Возведение в степень
    int result = 1;
    for (int i = 0; i < b; i++) {
        result = (result * a) % M;
    }
    cout << "(a^b) mod M = " << result << endl;

    // Поиск обратного элемента a
    int inverse_a = modInverse(a, M);
    if (inverse_a != -1) {
        cout << "a^(-1) mod M = " << inverse_a << endl;
    }
    else {
        cout << "a^(-1) mod M = нет решения" << endl;
    }

    // Поиск обратного элемента b
    int inverse_b = modInverse(b, M);
    if (inverse_b != -1) {
        cout << "b^(-1) mod M = " << inverse_b << endl;
    }
    else {
        cout << "b^(-1) mod M = нет решения" << endl;
    }

    // Деление
    if (inverse_a != -1) {
        cout << "(b/a) mod M = " << (b * inverse_a) % M << endl;
    }
    else {
        cout << "(b^a) mod M = нет решения" << endl;
    }

    if (inverse_b != -1) {
        cout << "(a/b) mod M = " << (a * inverse_b) % M << endl;
    }
    else {
        cout << "(a^b) mod M = нет решения" << endl;
    }
}