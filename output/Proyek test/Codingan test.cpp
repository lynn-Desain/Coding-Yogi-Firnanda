#include <iostream>
#include <algorithm>
#include <cctype>

int main() {
    std::string str;

    std::cout << "Upper/lowwer Algorithm\n";
    for (int i = 0; i < 4; i++) {
        std::cout << "Masukkan kalimat/Nama ke- " << (i + 1) << ": ";
        std::getline (std::cin, str);

        std::transform (str.begin(), str.end(), str.begin(), ::toupper)
        std::cout << "Setelah diubah ke huruf besar : " << str << std::endl;

        std::transform (str.begin(), str.end(), str.begin(),
            [](unsigner char c) { return std::tolower(c)}
    );
    std::cout << "Setelah diubah ke huruf kecil : " << str << std::endl;
    }
    return 0;
}