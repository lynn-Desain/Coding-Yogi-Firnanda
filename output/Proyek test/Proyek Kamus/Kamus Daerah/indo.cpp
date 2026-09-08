#include <iostream>
#include <map>
#include <string>
#include <fstream>  // Untuk baca/tulis file CSV
#include <iomanip>  // Untuk format output
#include <cctype>   // Untuk tolower
#include <sstream>  // Untuk parsing CSV sederhana

// Fungsi untuk mengisi data kamus default (contoh kata Banjar sederhana)
void isiKamusDefault(std::map<std::string, std::string>& idToBanjar, std::map<std::string, std::string>& banjarToId) {
    // Data default Indonesia -> Banjar (contoh sederhana; edit di CSV untuk lebih lengkap)
    idToBanjar["halo"] = "apa kabar";
    idToBanjar["terima kasih"] = "matur nuhun";
    idToBanjar["selamat pagi"] = "salam pagi";
    idToBanjar["nama"] = "ngaran";
    idToBanjar["rumah"] = "bubuhan";
    idToBanjar["makan"] = "mangan";
    idToBanjar["minum"] = "minum";
    idToBanjar["buku"] = "buku";
    idToBanjar["sekolah"] = "sekolahan";
    idToBanjar["teman"] = "kawan";

    // Isi map balik (Banjar -> Indonesia)
    for (auto& pair : idToBanjar) {
        banjarToId[pair.second] = pair.first;
    }
}

// Fungsi untuk membaca CSV dan isi kamus (input dari Excel/CSV)
bool loadDariCSV(std::map<std::string, std::string>& idToBanjar, std::map<std::string, std::string>& banjarToId) {
    std::ifstream file("kamus_banjar.csv");
    if (!file.is_open()) {
        std::cout << "File kamus_banjar.csv tidak ditemukan. Menggunakan data default." << std::endl;
        return false;
    }

    std::string line;
    bool headerSkipped = false;
    idToBanjar.clear();
    banjarToId.clear();

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string indonesia, banjar;
        std::getline(ss, indonesia, ',');
        if (!std::getline(ss, banjar, ',')) continue;  // Skip baris tidak lengkap

        // Trim whitespace sederhana (opsional, untuk kebersihan)
        indonesia.erase(0, indonesia.find_first_not_of(" \t"));
        indonesia.erase(indonesia.find_last_not_of(" \t") + 1);
        banjar.erase(0, banjar.find_first_not_of(" \t"));
        banjar.erase(banjar.find_last_not_of(" \t") + 1);

        // Skip header
        if (!headerSkipped) {
            if (indonesia == "Indonesia" && banjar == "Banjar") {
                headerSkipped = true;
                continue;
            } else {
                std::cout << "Format CSV salah (header tidak ditemukan). Menggunakan data default." << std::endl;
                file.close();
                return false;
            }
        }

        // Ubah ke lowercase untuk konsistensi (case-insensitive)
        for (char& c : indonesia) c = tolower(c);
        for (char& c : banjar) c = tolower(c);

        // Masukkan ke map (skip jika kosong atau duplikat)
        if (!indonesia.empty() && !banjar.empty() && idToBanjar.find(indonesia) == idToBanjar.end()) {
            idToBanjar[indonesia] = banjar;
            banjarToId[banjar] = indonesia;
        }
    }

    file.close();
    if (idToBanjar.empty()) {
        std::cout << "File CSV kosong atau tidak valid. Menggunakan data default." << std::endl;
        return false;
    }

    std::cout << "Berhasil load " << idToBanjar.size() << " entri dari kamus_banjar.csv!" << std::endl;
    return true;
}

// Fungsi terjemah Indonesia ke Banjar dengan tampilan menarik
void terjemahIdKeBanjar(const std::map<std::string, std::string>& idToBanjar) {
    std::string kata;
    std::cout << std::setw(40) << std::setfill('=') << "" << std::endl;
    std::cout << "Masukkan kata/frasa Indonesia: ";
    std::getline(std::cin, kata);
    for (char& c : kata) c = tolower(c);
    
    auto it = idToBanjar.find(kata);
    if (it != idToBanjar.end()) {
        std::cout << std::setw(20) << std::setfill(' ') << "Terjemahan Banjar:" << std::endl;
        std::cout << "  -> " << it->second << std::endl;
    } else {
        std::cout << "  Kata '" << kata << "' tidak ditemukan dalam kamus!" << std::endl;
        std::cout << "  Coba tambahkan di CSV dan load ulang." << std::endl;
    }
    std::cout << std::setw(40) << std::setfill('=') << "" << std::endl;
}

// Fungsi terjemah Banjar ke Indonesia dengan tampilan menarik
void terjemahBanjarKeId(const std::map<std::string, std::string>& banjarToId) {
    std::string kata;
    std::cout << std::setw(40) << std::setfill('=') << "" << std::endl;
    std::cout << "Masukkan kata/frasa Banjar: ";
    std::getline(std::cin, kata);
    for (char& c : kata) c = tolower(c);
    
    auto it = banjarToId.find(kata);
    if (it != banjarToId.end()) {
        std::cout << std::setw(20) << std::setfill(' ') << "Terjemahan Indonesia:" << std::endl;
        std::cout << "  -> " << it->second << std::endl;
    } else {
        std::cout << "  Kata '" << kata << "' tidak ditemukan dalam kamus!" << std::endl;
        std::cout << "  Coba tambahkan di CSV dan load ulang." << std::endl;
    }
    std::cout << std::setw(40) << std::setfill('=') << "" << std::endl;
}

// Fungsi ekspor ke CSV (output ke Excel)
void eksporKeCSV(const std::map<std::string, std::string>& idToBanjar) {
    std::ofstream file("kamus_banjar.csv");
    if (!file.is_open()) {
        std::cout << "Gagal membuat file CSV! Periksa izin folder." << std::endl;
        return;
    }
    
    // Header CSV
    file << "Indonesia,Banjar" << std::endl;
    
    // Tulis data (sorted by Indonesia untuk kemudahan edit)
    for (const auto& pair : idToBanjar) {
        file << pair.first << "," << pair.second << std::endl;
    }
    
    file.close();
    std::cout << "Data kamus berhasil diekspor ke 'kamus_banjar.csv'!" << std::endl;
    std::cout << "Buka di Excel, edit (tambah/hapus baris), simpan sebagai CSV, lalu load ulang via menu 4." << std::endl;
}

int main() {
    std::map<std::string, std::string> idToBanjar;
    std::map<std::string, std::string> banjarToId;
    
    // Tampilan selamat datang
    std::cout << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "|                                                              |"<< std::endl;
    std::cout << "|                  KAMUS MINI INDONESIA - BANJAR               |" << std::endl;
    std::cout << "|                                                              |" << std::endl;
    std::cout << "================================================================" << std::endl;
    std::cout << "Selamat datang!" << std::endl;
    
    // Coba load dari CSV, jika gagal gunakan default
    if (!loadDariCSV(idToBanjar, banjarToId)) {
        isiKamusDefault(idToBanjar, banjarToId);
        eksporKeCSV(idToBanjar);  // Export default agar bisa edit segera
        std::cout << "Menggunakan data default. Kamus diekspor ke CSV untuk edit." << std::endl;
    }
    
    int pilihan;
    do {
        // Menu dengan tampilan menarik
        std::cout << std::endl << std::string(60, '=') << std::endl;
        std::cout << "                  MENU KAMUS BANJAR" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "1. Terjemah Indonesia - Banjar" << std::endl;
        std::cout << "2. Terjemah Banjar - Indonesia" << std::endl;
        std::cout << "3. Ekspor Kamus ke CSV (Edit di Excel)" << std::endl;
        std::cout << "4. Load Ulang dari CSV (Update dari Excel)" << std::endl;
        std::cout << "5. Keluar" << std::endl;
        std::cout << std::string(60, '=') << std::endl;
        std::cout << "Pilih menu (1-5): ";
        std::cin >> pilihan;
        std::cin.ignore();  // Clear buffer untuk getline selanjutnya
        
        switch (pilihan) {
            case 1:
                terjemahIdKeBanjar(idToBanjar);
                break;
            case 2:
                terjemahBanjarKeId(banjarToId);
                break;
            case 3:
                eksporKeCSV(idToBanjar);
                break;
            case 4:
                if (loadDariCSV(idToBanjar, banjarToId)) {
                    std::cout << "Kamus berhasil diupdate dari CSV! Total entri: " << idToBanjar.size() << std::endl;
                } else {
                    std::cout << "Gagal load. Menggunakan data sebelumnya." << std::endl;
                }
                break;
            case 5:
                std::cout << std::endl << "================================================================" << std::endl;
                std::cout << "|                    Terima kasih! Matur nuhun!                |" << std::endl;
                std::cout << "================================================================" << std::endl;
                break;
            default:
                std::cout << "Pilihan tidak valid! Silakan pilih 1-5." << std::endl;
        }
    } while (pilihan != 5);
    
    return 0;
}
