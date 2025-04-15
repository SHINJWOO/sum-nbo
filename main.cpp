#include <iostream>
#include <fstream>
#include <cstdint>
#include <netinet/in.h> // ntohl을 위해 필요

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "사용법: " << argv[0] << " <파일1> [파일2>..." << "\n";
        return 1;
    }

    uint32_t total = 0;

    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i], std::ios::binary);
        if (!file) {
            std::cerr << "파일을 열 수 없습니다: " << argv[i] << "\n";
            return 1;
        }

        uint32_t num_network;
        file.read(reinterpret_cast<char*>(&num_network), sizeof(num_network));

        if (file.gcount() != sizeof(num_network)) {
            std::cerr << "잘못된 파일 크기 " << argv[i] << "\n";
            return 1;
        }

        uint32_t num_host = ntohl(num_network);

        if (i > 1) {
            std::cout << " + ";
        }
        std::cout << num_host << "(0x" << std::hex << num_host << std::dec << ")";

        total += num_host;
    }

    std::cout << " = " << total << "(0x" << std::hex << total << std::dec << ")";

    return 0;
}
