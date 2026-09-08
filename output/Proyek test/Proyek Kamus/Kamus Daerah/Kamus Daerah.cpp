#include <iostream>
#include <map>
#include <string>
#include <fstream>  // Untuk baca/tulis file CSV
#include <iomanip>  // Untuk format output
#include <cctype>   // Untuk tolower
#include <sstream>  // Untuk parsing CSV sederhana

// Fungsi untuk mengisi data kamus default (hardcoded, jika CSV gagal)
void isiKamusDefault(std::map<std::string, std::string>& idToBugis, std::map<std::string, std::string>& bugisToId) {
    idToBugis["halo"] = "ape kabar";
    idToBugis["terima kasih"] = "matsi";
    idToBugis["selamat pagi"] = "assalamualaikum";
    idToBugis["nama"] = "anna";
    idToBugis["rumah"] = "banua";
    idToBugis["makan"] = "mangan";
    idToBugis["minum"] = "minum";
    idToBugis["buku"] = "kitab";
    idToBugis["sekolah"] = "alléng";
    idToBugis["teman"] = "sombong";

    // Isi map balik (Bugis -> Indonesia)
    for (auto& pair : idToBugis) {
        bugisToId[pair.second] = pair.first;
    }
}

// Fungsi untuk membaca CSV dan isi kamus (input dari Excel/CSV)
bool loadDariCSV(std::map<std::string, std::string>& idToBugis, std::map<std::string, std::string>& bugisToId) {
    std::ifstream file("kamus.csv");
    if (!file.is_open()) {
        std::cout << "File kamus.csv tidak ditemukan. Menggunakan data default." << std::endl;
        return false;
    }

    std::string line;
    bool headerSkipped = false;
    idToBugis.clear();
    bugisToId.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string indonesia, bugis;
        std::getline(ss, indonesia, ',');
        std::getline(ss, bugis, ',');

        // Skip header
        if (!headerSkipped) {
            if (indonesia == "Indonesia" && bugis == "Bugis") {
                headerSkipped = true;
                continue;
            } else {
                std::cout << "Format CSV salah (header tidak ditemukan). Menggunakan data default." << std::endl;
                file.close();
                return false;
            }
        }

        // Ubah ke lowercase untuk konsistensi
        for (char& c : indonesia) c = tolower(c);
        for (char& c : bugis) c = tolower(c);

        // Masukkan ke map (skip jika kosong)
        if (!indonesia.empty() && !bugis.empty()) {
            idToBugis[indonesia] = bugis;
            bugisToId[bugis] = indonesia;
        }
    }

    file.close();
    if (idToBugis.empty()) {
        std::cout << "File CSV kosong atau tidak valid. Menggunakan data default." << std::endl;
        return false;
    }

    std::cout << "Berhasil load " << idToBugis.size() << " entri dari kamus.csv!" << std::endl;
    return true;
}

// Fungsi terjemah Indonesia ke Bugis
void terjemahIdKeBugis(const std::map<std::string, std::string>& idToBugis) {
    std::string kata;
    std::cout << "Masukkan kata Indonesia: ";
    std::getline(std::cin, kata);
    for (char& c : kata) c = tolower(c);
    
    auto it = idToBugis.find(kata);
    if (it != idToBugis.end()) {
        std::cout << "Terjemahan Bugis: " << it->second << std::endl;
    } else {
        std::cout << "Kata tidak ditemukan dalam kamus!" << std::endl;
    }
}

// Fungsi terjemah Bugis ke Indonesia
void terjemahBugisKeId(const std::map<std::string, std::string>& bugisToId) {
    std::string kata;
    std::cout << "Masukkan kata Bugis: ";
    std::getline(std::cin, kata);
    for (char& c : kata) c = tolower(c);
    
    auto it = bugisToId.find(kata);
    if (it != bugisToId.end()) {
        std::cout << "Terjemahan Indonesia: " << it->second << std::endl;
    } else {
        std::cout << "Kata tidak ditemukan dalam kamus!" << std::endl;
    }
}

// Fungsi ekspor ke CSV (output ke Excel)
void eksporKeCSV(const std::map<std::string, std::string>& idToBugis) {
    std::ofstream file("kamus.csv");
    if (!file.is_open()) {
        std::cout << "Gagal membuat file CSV!" << std::endl;
        return;
    }
    
    // Header CSV
    file << "Indonesia,Bugis" << std::endl;
    
    // Tulis data
    for (const auto& pair : idToBugis) {
        file << pair.first << "," << pair.second << std::endl;
    }
    
    file.close();
    std::cout << "Data kamus berhasil diekspor ke 'kamus.csv'. Edit di Excel, lalu load ulang!" << std::endl;
}

int main() {
    std::map<std::string, std::string> idToBugis;
    std::map<std::string, std::string> bugisToId;
    
    // Coba load dari CSV, jika gagal gunakan default
    if (!loadDariCSV(idToBugis, bugisToId)) {
        isiKamusDefault(idToBugis, bugisToId);
        // Ekspor default ke CSV untuk pertama kali
        eksporKeCSV(idToBugis);
    }
    
    int pilihan;
    do {
        std::cout << "\n=== KAMUS MINI INDONESIA - BUGIS (dari Excel/CSV) ===" << std::endl;
        std::cout << "1. Terjemah Indonesia ke Bugis" << std::endl;
        std::cout << "2. Terjemah Bugis ke Indonesia" << std::endl;
        std::cout << "3. Ekspor Kamus ke CSV (untuk edit di Excel)" << std::endl;
        std::cout << "4. Load Ulang dari CSV (input dari Excel)" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << "Pilih menu (1-5): ";
        std::cin >> pilihan;
        std::cin.ignore();  // Clear buffer untuk getline
        
        switch (pilihan) {
            case 1:
                terjemahIdKeBugis(idToBugis);
                break;
            case 2:
                terjemahBugisKeId(bugisToId);
                break;
            case 3:
                eksporKeCSV(idToBugis);
                break;
            case 4:
                if (loadDariCSV(idToBugis, bugisToId)) {
                    std::cout << "Kamus berhasil diupdate dari CSV!" << std::endl;
                }
                break;
            case 5:
                std::cout << "Terima kasih! Selamat tinggal." << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid!" << std::endl;
        }
    } while (pilihan != 5);
    
    return 0;
}