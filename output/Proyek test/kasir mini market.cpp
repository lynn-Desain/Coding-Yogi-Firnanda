#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>  // Untuk format output
#include <ctime>    // Untuk timestamp
#include <sstream>  // Untuk stringstream

// Struktur untuk item barang
struct Item {
    std::string nama;
    int jumlah;
    double harga;
    double subtotal() const { return jumlah * harga; }
};

// Fungsi untuk mendapatkan timestamp
std::string getTimestamp() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localTime);
    return std::string(buffer);
}

// Fungsi untuk nomor transaksi (sederhana, berdasarkan counter di file log)
int getNextTransactionNumber() {
    std::ifstream logFile("log_kasir.txt");
    int nextNum = 1;
    if (logFile.is_open()) {
        std::string line;
        while (std::getline(logFile, line)) {
            if (line.find("Transaksi #") != std::string::npos) {
                std::stringstream ss(line);
                std::string temp;
                ss >> temp;  // "Transaksi"
                ss >> temp;  // "#"
                ss >> temp;  // nomor
                nextNum = std::stoi(temp.substr(1)) + 1;  // Ambil angka setelah #
            }
        }
        logFile.close();
    }
    return nextNum;
}

// Fungsi untuk simpan transaksi ke file struk
void simpanStruk(const std::vector<Item>& items, double total, double diskon, double pembayaran, double kembalian, int nomorTransaksi) {
    std::string filename = "transaksi_" + std::to_string(nomorTransaksi) + ".txt";
    std::ofstream file(filename);
    if (file.is_open()) {
        std::string timestamp = getTimestamp();
        file << "=== STRUK KASIR MINI MARKET ===" << std::endl;
        file << "Tanggal/Waktu: " << timestamp << std::endl;
        file << "Nomor Transaksi: #" << nomorTransaksi << std::endl;
        file << "=================================" << std::endl;
        file << std::left << std::setw(20) << "Barang" << std::setw(10) << "Jumlah" 
             << std::setw(10) << "Harga" << std::setw(10) << "Subtotal" << std::endl;
        file << "=================================" << std::endl;
        
        double subtotalTotal = 0;
        for (const auto& item : items) {
            file << std::left << std::setw(20) << item.nama 
                 << std::setw(10) << item.jumlah 
                 << std::setw(10) << "Rp " << std::fixed << std::setprecision(0) << item.harga 
                 << std::setw(10) << "Rp " << std::fixed << std::setprecision(0) << item.subtotal() << std::endl;
            subtotalTotal += item.subtotal();
        }
        
        file << "=================================" << std::endl;
        file << std::left << std::setw(30) << "Subtotal:" << "Rp " << std::fixed << std::setprecision(0) << subtotalTotal << std::endl;
        file << std::left << std::setw(30) << "Diskon (" << diskon << "%):" << "Rp -" << std::fixed << std::setprecision(0) << (subtotalTotal * diskon / 100) << std::endl;
        file << std::left << std::setw(30) << "Total Akhir:" << "Rp " << std::fixed << std::setprecision(0) << total << std::endl;
        file << std::left << std::setw(30) << "Pembayaran:" << "Rp " << std::fixed << std::setprecision(0) << pembayaran << std::endl;
        file << std::left << std::setw(30) << "Kembalian:" << "Rp " << std::fixed << std::setprecision(0) << kembalian << std::endl;
        file << "=================================" << std::endl;
        file << "Terima kasih telah berbelanja!" << std::endl;
        file.close();
        
        // Tambahkan ke log keseluruhan
        std::ofstream logFile("log_kasir.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "Transaksi #" << nomorTransaksi << " - " << timestamp << " - Total: Rp " << total << std::endl;
            logFile.close();
        }
        
        std::cout << "Struk disimpan ke file: " << filename << std::endl;
    } else {
        std::cout << "Error: Tidak bisa simpan file struk!" << std::endl;
    }
}

// Fungsi untuk tampilkan riwayat dari log
void tampilkanRiwayat() {
    std::ifstream logFile("log_kasir.txt");
    if (!logFile.is_open()) {
        std::cout << "Belum ada riwayat transaksi." << std::endl;
        return;
    }
    
    std::cout << "=== RIWAYAT TRANSAKSI ===" << std::endl;
    std::string line;
    while (std::getline(logFile, line)) {
        std::cout << line << std::endl;
    }
    logFile.close();
}

int main() {
    std::vector<Item> keranjang;
    int pilihan;
    bool transaksiAktif = false;
    int nomorTransaksi = 0;

    std::cout << "=== SISTEM KASIR MINI MARKET ===" << std::endl;
    std::cout << "Selamat datang! Pilih opsi:" << std::endl;
    std::cout << "1. Mulai Transaksi Baru" << std::endl;
    std::cout << "2. Lihat Riwayat Transaksi" << std::endl;
    std::cout << "3. Keluar" << std::endl;

    while (true) {
        std::cout << "\nMasukkan pilihan (1-3): ";
        std::cin >> pilihan;
        std::cin.ignore();  // Bersihkan buffer

        if (pilihan == 3) {
            std::cout << "Terima kasih! Sampai jumpa." << std::endl;
            break;
        } else if (pilihan == 2) {
            tampilkanRiwayat();
            continue;
        } else if (pilihan == 1) {
            if (transaksiAktif) {
                std::cout << "Transaksi masih aktif. Selesaikan dulu atau mulai baru?" << std::endl;
                continue;
            }
            transaksiAktif = true;
            keranjang.clear();
            nomorTransaksi = getNextTransactionNumber();
            std::cout << "Transaksi baru dimulai. Nomor: #" << nomorTransaksi << std::endl;

            // Loop input barang
            while (true) {
                std::cout << "\n--- Input Barang ---" << std::endl;
                std::cout << "1. Tambah Barang" << std::endl;
                std::cout << "2. Selesai Input & Konfirmasi" << std::endl;
                std::cout << "Pilih: ";
                std::cin >> pilihan;
                std::cin.ignore();

                if (pilihan == 2) {
                    break;
                } else if (pilihan == 1) {
                    Item item;
                    std::cout << "Nama barang: ";
                    std::getline(std::cin, item.nama);
                    std::cout << "Jumlah: ";
                    std::cin >> item.jumlah;
                    if (item.jumlah <= 0) {
                        std::cout << "Jumlah harus positif!" << std::endl;
                        continue;
                    }
                    std::cout << "Harga per unit (Rp): ";
                    std::cin >> item.harga;
                    if (item.harga <= 0) {
                        std::cout << "Harga harus positif!" << std::endl;
                        continue;
                    }
                    std::cin.ignore();
                    keranjang.push_back(item);
                    std::cout << "Barang ditambahkan. Subtotal: Rp " << item.subtotal() << std::endl;
                }
            }

            if (keranjang.empty()) {
                std::cout << "Tidak ada barang. Transaksi dibatalkan." << std::endl;
                transaksiAktif = false;
                continue;
            }

            // Tampilkan ringkasan (sikon)
            double subtotalTotal = 0;
            std::cout << "\n=== RINGKASAN TRANSAKSI ===" << std::endl;
            std::cout << std::left << std::setw(20) << "Barang" << std::setw(10) << "Jumlah" 
                  << std::setw(10) << "Harga" << std::setw(10) << "Subtotal" << std::endl;
            std::cout << "=================================" << std::endl;
            for (const auto& item : keranjang) {
                std::cout << std::left << std::setw(20) << item.nama 
                     << std::setw(10) << item.jumlah 
                     << std::setw(10) << "Rp " << std::fixed << std::setprecision(0) << item.harga 
                     << std::setw(10) << "Rp " << std::fixed << std::setprecision(0) << item.subtotal() << std::endl;
                subtotalTotal += item.subtotal();
            }
            std::cout << "=================================" << std::endl;
            std::cout << std::left << std::setw(30) << "Subtotal:" << "Rp " << std::fixed << std::setprecision(0) << subtotalTotal << std::endl;

            // Input diskon
            double diskonPersen = 0;
            std::cout << "Diskon (%) [0 untuk tidak ada]: ";
            std::cin >> diskonPersen;
            double diskonNilai = subtotalTotal * diskonPersen / 100;
            double totalAkhir = subtotalTotal - diskonNilai;
            std::cout << "Diskon: Rp " << std::fixed << std::setprecision(0) << diskonNilai << std::endl;
            std::cout << "Total Akhir: Rp " << std::fixed << std::setprecision(0) << totalAkhir << std::endl;

            // Konfirmasi pembayaran
            double pembayaran;
            std::cout << "Jumlah pembayaran (Rp): ";
            std::cin >> pembayaran;
            if (pembayaran < totalAkhir) {
                std::cout << "Pembayaran kurang! Transaksi dibatalkan." << std::endl;
                transaksiAktif = false;
                continue;
            }
            double kembalian = pembayaran - totalAkhir;
            std::cout << "Kembalian: Rp " << std::fixed << std::setprecision(0) << kembalian << std::endl;

            // Konfirmasi akhir
            std::cout << "\nKonfirmasi transaksi? (y/n): ";
            char konfirm;
            std::cin >> konfirm;
            if (konfirm == 'y' || konfirm == 'Y') {
                simpanStruk(keranjang, totalAkhir, diskonPersen, pembayaran, kembalian, nomorTransaksi);
                std::cout << "Transaksi selesai dan disimpan!" << std::endl;
            } else {
                std::cout << "Transaksi dibatalkan." << std::endl;
            }
            transaksiAktif = false;
        } else {
            std::cout << "Pilihan tidak valid!" << std::endl;
        }
    }

    return 0;
}
