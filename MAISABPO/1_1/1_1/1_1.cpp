#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

vector<unsigned char> read_file(string file_path) {
    ifstream file(file_path, ios::binary);
    if (!file) {
        throw "Ошибка открытия файла";
    }
    vector<unsigned char> data(istreambuf_iterator<char>(file), {});
    return data;
}

void print_bytes(vector<unsigned char>data, string format_type) {
    if (format_type == "hex8") {
        for (const auto& byte : data) {
            cout << setw(2) << setfill('0') << hex << static_cast<int>(byte) << ' ';
        }
    }
    else if (format_type == "dec8") {
        for (const auto& byte : data) {
            cout << setw(3) << setfill('0') << dec << static_cast<int>(byte) << ' ';
        }
    }
    else if (format_type == "hex16") {
        for (const auto& byte : data) {
            cout << setw(4) << setfill('0') << hex << static_cast<int>(byte) << ' ';
        }
    }
    else if (format_type == "dec16") {
        for (const auto& byte : data) {
            cout << setw(5) << setfill('0') << dec << static_cast<int>(byte) << ' ';
        }
    }
    else if (format_type == "hex32") {
        for (const auto& byte : data) {
            cout << setw(8) << setfill('0') << hex << static_cast<int>(byte) << ' ';
        }
    }
    else {
        cout << "Неверный формат файла" << endl;
    }
}

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "Russian");

    string format_type = argv[1];
    string file_path = argv[2];

    vector<unsigned char> data = read_file(file_path);
    print_bytes(data, format_type);

    return 0;
}