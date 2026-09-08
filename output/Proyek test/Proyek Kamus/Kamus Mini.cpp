#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>

class MiniDictionary {
private:
    std::map<std::string, std::string> dictionary;  // Kamus: ID -> EN
    const std::string filename = "kamus.txt";       // Nama file untuk simpan/muat

public:
    // Fungsi untuk memuat data dari file
    void loadFromFile() {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "File " << filename << " tidak ditemukan. Mulai dengan kamus kosong." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            size_t colonPos = line.find(':');
            if (colonPos != std::string::npos) {
                std::string idWord = line.substr(0, colonPos);
                std::string enWord = line.substr(colonPos + 1);
                dictionary[idWord] = enWord;
            }
        }
        file.close();
        std::cout << "Data kamus dimuat dari file. Total entri: " << dictionary.size() << std::endl;
    }

    // Fungsi untuk menyimpan data ke file
    void saveToFile() {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cout << "Gagal membuka file untuk simpan!" << std::endl;
            return;
        }

        for (const auto& pair : dictionary) {
            file << pair.first << ":" << pair.second << std::endl;
        }
        file.close();
        std::cout << "Data kamus disimpan ke file " << filename << std::endl;
    }

    // Fungsi untuk menambah kata baru
    void addWord() {
        std::string idWord, enWord;
        std::cout << "Masukkan kata dalam Bahasa Indonesia: ";
        std::cin.ignore();  // Clear buffer
        std::getline(std::cin, idWord);
        std::cout << "Masukkan arti dalam Bahasa Inggris: ";
        std::getline(std::cin, enWord);

        if (dictionary.find(idWord) != dictionary.end()) {
            std::cout << "Kata '" << idWord << "' sudah ada. Arti saat ini: " << dictionary[idWord] << std::endl;
            char update;
            std::cout << "Ingin mengupdate? (y/n): ";
            std::cin >> update;
            if (update != 'y' && update != 'Y') {
                return;
            }
        }

        dictionary[idWord] = enWord;
        std::cout << "Kata '" << idWord << "' berhasil ditambahkan dengan arti '" << enWord << "'." << std::endl;
    }

    // Fungsi untuk mencari arti
    void searchWord() {
        std::string idWord;
        std::cout << "Masukkan kata dalam Bahasa Indonesia untuk dicari: ";
        std::cin.ignore();  // Clear buffer
        std::getline(std::cin, idWord);

        auto it = dictionary.find(idWord);
        if (it != dictionary.end()) {
            std::cout << "Arti '" << idWord << "' dalam Bahasa Inggris: " << it->second << std::endl;
        } else {
            std::cout << "Kata '" << idWord << "' tidak ditemukan dalam kamus." << std::endl;
        }
    }

    // Fungsi untuk menampilkan semua entri (opsional, untuk debug)
    void displayAll() {
        if (dictionary.empty()) {
            std::cout << "Kamus kosong." << std::endl;
            return;
        }
        std::cout << "\nDaftar Kamus Saat Ini:" << std::endl;
        for (const auto& pair : dictionary) {
            std::cout << "- " << pair.first << ": " << pair.second << std::endl;
        }
        std::cout << "Total entri: " << dictionary.size() << std::endl;
    }
};

int main() {
    MiniDictionary kamus;
    kamus.loadFromFile();  // Muat data dari file saat start

    char choice;
    std::cout << "=== KAMUS MINI BAHASA INDONESIA - INGGRIS ===" << std::endl;
    std::cout << "1. Tambah kata baru" << std::endl;
    std::cout << "2. Cari arti kata" << std::endl;
    std::cout << "3. Tampilkan semua kata" << std::endl;
    std::cout << "4. Simpan ke file" << std::endl;
    std::cout << "5. Keluar" << std::endl;

    do {
        std::cout << "\nPilih menu (1-5): ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                kamus.addWord();
                break;
            case '2':
                kamus.searchWord();
                break;
            case '3':
                kamus.displayAll();
                break;
            case '4':
                kamus.saveToFile();
                break;
            case '5':
                kamus.saveToFile();  // Simpan otomatis saat keluar
                std::cout << "Terima kasih telah menggunakan Kamus Mini!" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid. Silakan pilih 1-5." << std::endl;
        }
    } while (choice != '5');

    return 0;
}
