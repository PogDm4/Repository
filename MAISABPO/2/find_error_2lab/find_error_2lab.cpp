typedef unsigned char byte;
typedef unsigned int uint;
#include <iostream>
#include <random>
#include <bitset>
#include <Windows.h>
//#include <GF256.h>

using namespace std;

uint chksum_xor(byte*, int n);
uint crc16(byte*, int n);
uint crc32(byte*, int n);

int main()
{
    int N = 4;
    byte* memory = new byte[N];
    time_t t = time(nullptr);
    srand(t);

    for (int i = 0; i < N; ++i)
        memory[i] = (byte)rand();

    uint result[32][4] = { 0 };

    int detection_xor = 0;
    int detection_crc16 = 0;
    int detection_crc32 = 0;

    for (uint i = 1; i < UINT_MAX; ++i) {
        uint chksum_xor_0 = chksum_xor(memory, N);
        uint chksum_crc16_0 = crc16(memory, N);
        uint chksum_crc32_0 = crc32(memory, N);

        uint data32 = 0;
        for (int i = 0; i < 4; ++i) {
            data32 = (data32 << 8) + memory[i];
        }

        data32 = data32 ^ i;

        for (int i = 0; i < 4; ++i) {
            memory[3 - i] = (data32 >> (8 * i)) & 0xFF;
        }

        uint chksum_xor_1 = chksum_xor(memory, N);
        uint chksum_crc16_1 = crc16(memory, N);
        uint chksum_crc32_1 = crc32(memory, N);

        int bits_in_i = bitset<32>(i).count();
        result[bits_in_i - 1][0]++;

        if (chksum_xor_0 != chksum_xor_1) {
            detection_xor++;
            result[bits_in_i - 1][1]++;
        }

        if (chksum_crc16_0 != chksum_crc16_1) {
            detection_crc16++;
            result[bits_in_i - 1][2]++;
        }

        if (chksum_crc32_0 != chksum_crc32_1) {
            detection_crc32++;
            result[bits_in_i - 1][3]++;
        }

        if (i % 100000000 == 0) {
            cout << "Iteration " << i << endl;
        }
    }

    for (int i = 0; i < 32; ++i) {
        cout << i + 1 << " ";
        for (int j = 0; j < 4; ++j) {
            cout << result[i][j] << " ";
        }
        cout << endl;
    }

    delete[] memory;
    return 0;
}

uint chksum_xor(byte* data, int N)
{
    uint chk = 0;
    for (int n = 0; n < N; ++n)
    {
        chk ^= data[n];
    }
    return chk;
}

uint crc16(byte* data, int N) {
    const uint polynomial = 0x8005;
    uint crc = 0;

    for (int i = 0; i < N; ++i) {
        crc ^= (uint)data[i] << 8;
        for (int j = 0; j < 8; ++j) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ polynomial;
            }
            else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

uint crc32(byte* data, int N) {
    const uint polynomial = 0xEDB88320;
    uint crc = 0xFFFFFFFF;

    for (int i = 0; i < N; ++i) {
        crc ^= (uint)data[i];
        for (int j = 0; j < 8; ++j) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            }
            else {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}

//uint Solomon(byte* data, int N) {
//    uint K = 255 - N; // Количество исправляемых ошибок
//    GF256::init_gf256();
//
//    byte data_out[K];
//    byte parity[K];
//    GF256::RS(N, K, data, data_out, parity); // data_out содержит исходные данные; parity содержит байты для исправления ошибок
//}

//#include <iostream>
//#include <cstdint>
//#include <vector>
//#include <algorithm>
//
//#define USER_DATA_SIZE 2048
//#define N_BYTES_DAMAGE 6
//#define RAW_SECTOR_SIZE 2352
//#define USER_DATA_OFFSET 16
//
//struct RAW_SECTOR_MODE1 {
//    std::vector<uint8_t> SYNC;
//    std::vector<uint8_t> ADDR;
//    std::vector<uint8_t> EDC;
//    std::vector<uint8_t> P;
//    std::vector<uint8_t> Q;
//    std::vector<uint8_t> USER_DATA;
//    std::vector<uint8_t> Raw;
//};
//
//void printData(const std::vector<uint8_t>& data) {
//    int c = 0;
//    for (uint8_t byte : data) {
//        if (c == 32) {
//            std::cout << std::endl;
//            c = 0;
//        }
//        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << +byte << " ";
//        c++;
//    }
//    std::cout << std::endl;
//}
//
//int GenECCAndEDC_Mode1(std::vector<uint8_t>& user_data, std::vector<uint8_t>& stub_head, std::vector<uint8_t>& raw_sector) {
//    // Your GenECCAndEDC_Mode1 implementation here
//    return 0; // Replace with actual result
//}
//
//int CheckSector(std::vector<uint8_t>& raw_sector, int mode) {
//    // Your CheckSector implementation here
//    return 0; // Replace with actual result
//}
//
//int main() {
//    int a, d;
//    std::vector<uint8_t> stub_head(4, 0);
//    std::vector<uint8_t> user_data(USER_DATA_SIZE, 0);
//
//    // Initialize user data
//    std::cout << "Initialization of user data" << std::endl;
//    for (a = 0; a < USER_DATA_SIZE; a++) {
//        user_data[a] = static_cast<uint8_t>(a);
//    }
//
//    stub_head[3] = 1;
//
//    printData(user_data);
//
//    // Generate Reed-Solomon codes based on user data
//    std::cout << "Generating Reed-Solomon codes based on user data" << std::endl;
//    a = GenECCAndEDC_Mode1(user_data, stub_head, sectorForDamage.Raw);
//    if (a == 0) {
//        std::cout << "Error during Reed-Solomon code generation" << std::endl;
//        return -1;
//    }
//
//    // Copy the raw sector for comparison
//    sectorForCompare.Raw = sectorForDamage.Raw;
//
//    std::cout << "SYNC=" << std::endl;
//    printData(sectorForCompare.SYNC);
//    std::cout << "ADDR=" << std::endl;
//    printData(sectorForCompare.ADDR);
//    std::cout << "EDC=" << std::endl;
//    printData(sectorForCompare.EDC);
//    std::cout << "P=" << std::endl;
//    printData(sectorForCompare.P);
//    std::cout << "Q=" << std::endl;
//    printData(sectorForCompare.Q);
//    std::cout << "USER_DATA=" << std::endl;
//    printData(sectorForCompare.USER_DATA);
//
//    // Intentionally distort user data
//    std::cout << "Intentionally distorting user data" << std::endl;
//    for (a = 0; a < N_BYTES_DAMAGE; a++) {
//        sectorForDamage.Raw[a + USER_DATA_OFFSET] ^= 0xFF;
//    }
//
//    // Check for distortions
//    std::cout << "Checking for distortions: ";
//    d = 0;
//    for (a = 0; a < N_BYTES_DAMAGE; a++) {
//        d |= sectorForDamage.Raw[a + USER_DATA_OFFSET] ^ sectorForCompare.Raw[a + USER_DATA_OFFSET];
//    }
//    if (d == 0) {
//        std::cout << "No distortions occurred" << std::endl;
//        return -1;
//    }
//    std::cout << "Distortions are present" << std::endl;
//    printData(sectorForDamage.USER_DATA);
//
//    // Check the integrity of user data
//    std::cout << "Checking the integrity of user data" << std::endl;
//    a = CheckSector(sectorForDamage.Raw, 0);
//    if (a != 0) {
//        std::cout << "Integrity check did not detect errors" << std::endl;
//        return -1;
//    }
//
//    // Restore user data
//    a = CheckSector(sectorForDamage.Raw, 1);
//    if (a == 0) {
//        std::cout << "Data was not restored" << std::endl;
//        return -1;
//    }
//    std::cout << "Data restored!" << std::endl;
//    printData(sectorForDamage.USER_DATA);
//
//    return 0;
//}