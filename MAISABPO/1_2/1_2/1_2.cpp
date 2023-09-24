#include <iostream>
#include <sstream>
#include <bitset>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Russian");

	string command = argv[1];
	unsigned long long number1 = stoull(argv[2]);
	unsigned long long number2 = stoull(argv[3]);

	unsigned long long result;

	if (command == "xor") {
		result = number1 ^ number2;
	}
	else if (command == "and") {
		result = number1 & number2;
	}
	else if (command == "or") {
		result = number1 | number2;
	}
	else if (command == "set1") {
		result = number2 | (1ULL << number1);
	}
	else if (command == "set0") {
		result = number2 & ~(1ULL << number1);
	}
	else if (command == "shl") {
		result = number2 << number1;
	}
	else if (command == "shr") {
		result = number2 >> number1;
	}
	else if (command == "rol") {
		result = (number2 << number1) | (number2 >> (64 - number1));
	}
	else if (command == "ror") {
		result = (number2 >> number1) | (number2 << (64 - number1));
	}
	else if (command == "mix") {
		bitset<8> bits(number2);

		vector<int> digits;
		while (number1 > 0) {
			digits.insert(digits.begin(), number1 % 10);
			number1 /= 10;
		}

		bitset<8> mix;
		for (int i = 0; i != 8; ++i) {
			mix[digits[i]] = bits[i];
		}
		result = mix.to_ulong();
	}
	else {
		cout << "Неверная команда" << endl;
	}

	cout << "dec: " << result << endl;
	cout << "hex: " << hex << result << endl;
	cout << "bin: " << bitset<64>(result) << endl;
}