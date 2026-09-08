#include <iostream>
#include <iomanip>  // Untuk pengaturan format output (precision)

int main() {
    double idrAmount;  // Jumlah Rupiah yang dimasukkan
    char choice;       // Pilihan untuk lanjut atau keluar
    
    // Kurs tetap (dalam IDR per 1 unit mata uang asing)
    const double USD_RATE = 15000.0;
    const double EUR_RATE = 16500.0;
    const double JPY_RATE = 100.0;
    
    std::cout << "=== APLIKASI KONVERSI MATA UANG ===" << std::endl;
    std::cout << "Kurs yang digunakan:" << std::endl;
    std::cout << "1 USD = " << USD_RATE << " IDR" << std::endl;
    std::cout << "1 EUR = " << EUR_RATE << " IDR" << std::endl;
    std::cout << "1 JPY = " << JPY_RATE << " IDR" << std::endl;
    std::cout << "===================================" << std::endl;
    
    do {
        // Input jumlah Rupiah
        std::cout << "\nMasukkan jumlah Rupiah (IDR): ";
        std::cin >> idrAmount;
        
        if (idrAmount < 0) {
            std::cout << "Jumlah tidak boleh negatif! Silakan masukkan ulang." << std::endl;
            continue;
        }
        
        // Hitung konversi
        double usdAmount = idrAmount / USD_RATE;
        double eurAmount = idrAmount / EUR_RATE;
        double jpyAmount = idrAmount / JPY_RATE;
        
        // Output hasil dengan 2 desimal
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "\nHasil Konversi:" << std::endl;
        std::cout << idrAmount << " IDR = " << usdAmount << " USD" << std::endl;
        std::cout << idrAmount << " IDR = " << eurAmount << " EUR" << std::endl;
        std::cout << idrAmount << " IDR = " << jpyAmount << " JPY" << std::endl;
        
        // Tanya apakah ingin lanjut
        std::cout << "\nIngin konversi lagi? (y/n): ";
        std::cin >> choice;
        
    } while (choice == 'y' || choice == 'Y');
    
    std::cout << "Terima kasih telah menggunakan aplikasi ini!" << std::endl;
    return 0;
}
