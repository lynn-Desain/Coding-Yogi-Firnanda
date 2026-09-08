#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm> // Untuk transform (case-insensitive)
#include <vector>

int main() {
    std::map<std::string, std::string> idToEn;
    std::map<std::string, std::string> enToId;

    // Fungsi untuk memuat kamus dari file
    auto loadDictionary = [](std::map<std::string, std::string>& idToEn, std::map<std::string, std::string>& enToId, const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "Peringatan: File '" << filename << "' tidak ditemukan. Kamus kosong. Silakan buat file dengan format 'kata_id|terjemahan_en' per baris." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue; // Skip baris kosong atau komentar

            std::stringstream ss(line);
            std::string idWord, enWord;
            std::getline(ss, idWord, '|');
            std::getline(ss, enWord, '|');

            if (!idWord.empty() && !enWord.empty()) {
                // Konversi ke lowercase untuk case-insensitive
                std::transform(idWord.begin(), idWord.end(), idWord.begin(), ::tolower);
                std::transform(enWord.begin(), enWord.end(), enWord.begin(), ::tolower);

                idToEn[idWord] = enWord;
                enToId[enWord] = idWord;
            }
        }
        file.close();
        std::cout << "Kamus dimuat dari file '" << filename << "' dengan " << idToEn.size() << " entri." << std::endl;
    };

    // Muat kamus dari file
    loadDictionary(idToEn, enToId, "kamus.txt");

    std::string input;
    int pilihan;

    std::cout << "=== Kamus Besar Bahasa Indonesia - Inggris ===" << std::endl;
    std::cout << "Pilih opsi:" << std::endl;
    std::cout << "1. Cari terjemahan Indonesia ke Inggris" << std::endl;
    std::cout << "2. Cari terjemahan Inggris ke Indonesia" << std::endl;
    std::cout << "3. Tampilkan jumlah entri" << std::endl;
    std::cout << "4. Keluar" << std::endl;

    while (true) {
        std::cout << "\nMasukkan pilihan (1-4): ";
        std::cin >> pilihan;
        std::cin.ignore(); // Membersihkan buffer input

        if (pilihan == 4) {
            std::cout << "Terima kasih! Selamat tinggal." << std::endl;
            break;
        } else if (pilihan == 3) {
            std::cout << "Jumlah entri dalam kamus: " << idToEn.size() << std::endl;
            continue;
        } else if (pilihan == 1 || pilihan == 2) {
            if (idToEn.empty()) {
                std::cout << "Kamus kosong. Silakan muat file kamus.txt terlebih dahulu." << std::endl;
                continue;
            }

            std::cout << "Masukkan kata yang ingin dicari: ";
            std::getline(std::cin, input);

            // Konversi input ke lowercase
            std::transform(input.begin(), input.end(), input.begin(), ::tolower);

            std::map<std::string, std::string>* kamus = (pilihan == 1) ? &idToEn : &enToId;
            auto it = kamus->find(input);

            if (it != kamus->end()) {
                std::cout << "Terjemahan: " << it->second << std::endl;
            } else {
                std::cout << "Maaf, kata '" << input << "' tidak ditemukan dalam kamus." << std::endl;
                std::cout << "Coba kata lain atau tambahkan ke file kamus.txt." << std::endl;
            }
        } else {
            std::cout << "Pilihan tidak valid. Silakan pilih 1, 2, 3, atau 4." << std::endl;
        }

        // Tampilkan menu lagi
        std::cout << "\nPilih opsi:" << std::endl;
        std::cout << "1. Cari terjemahan Indonesia ke Inggris" << std::endl;
        std::cout << "2. Cari terjemahan Inggris ke Indonesia" << std::endl;
        std::cout << "3. Tampilkan jumlah entri" << std::endl;
        std::cout << "4. Keluar" << std::endl;
    }

    return 0;
}
