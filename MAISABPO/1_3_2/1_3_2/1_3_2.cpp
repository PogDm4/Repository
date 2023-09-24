#include <iostream>

using namespace std;

int mult(int a, int b, int m)
{
    int res = 0;
    while (b > 0)
    {
        if ((b & 1) != 0)
        {
            res ^= a;
            if (res >= m) res ^= m;
        }
        a <<= 1;
        if (a >= m) a ^= m;
        b >>= 1;
    }
    return res;
}

int ModInverse(int a, int m)
{
    a %= m;
    for (int i = 1; i < m; i++) {
        if (mult(a, i, m) == 1)
        {
            return i;
        }
    }
    return 1;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int a = 365;
    int b = 1514;
    int m = 69665;

    //сложение
    cout << "(a + b) mod M = " << (a ^ b) % m << endl;

    //вычитание
    cout << "(a - b) mod M= " << (a ^ b) % m << endl;

    //умножение
    cout << "(a * b) mod M = " << mult(a, b, m) << endl;

    //обратный элемент
    cout << "a^(-1) mod M = " << ModInverse(b, m) << endl;
}