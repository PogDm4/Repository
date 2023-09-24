#include <iostream>
#include <vector>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Введите n:" << endl;
	int n;
	cin >> n;
	vector<bool>A(n + 1, true);
	for (int i = 2; pow(i, 2) <= n; ++i) {
		if (A[i] == true) {
			for (int j = pow(i, 2); j <= n; j = j + i) {
				A[j] = false;
			}
		}
	}
	cout << "N первых простых чисел:" << endl;
	for (int i = 2; i != A.size(); ++i) {
		if (A[i] == true) {
			cout << i << " ";
		}
	}
	cout << endl;
	if (A[n] == true) {
		cout << n << "-простое" << endl;
	}
	else {
		cout << n << "-не простое" << endl;
	}
}