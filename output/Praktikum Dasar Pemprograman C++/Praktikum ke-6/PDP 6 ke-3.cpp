#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <cctype>

using namespace std;

// Fungsi untuk konversi huruf ke biner
string hurufKeBiner(char huruf) {
    if (isalpha(huruf)) {
        huruf = toupper(huruf);
        bitset<8> binary(huruf);
        return binary.to_string();
    }
    return "00000000"; // Default jika bukan huruf
}

// Fungsi untuk konversi string ke biner
string stringKeBiner(const string& teks) {
    string hasil = "";
    for (char c : teks) {
        if (isalpha(c)) {
            hasil += hurufKeBiner(c) + " ";
        }
    }
    return hasil;
}

// Fungsi untuk operasi XOR antar huruf
char xorHuruf(char huruf1, char huruf2) {
    huruf1 = toupper(huruf1);
    huruf2 = toupper(huruf2);
    
    int hasilXOR = huruf1 ^ huruf2;
    return static_cast<char>(hasilXOR);
}

// Fungsi untuk menampilkan header dengan nama
void tampilkanHeader(const string& nama) {
    cout << "==========================================" << endl;
    cout << "      KALKULATOR BINER - " << nama << endl;
    cout << "==========================================" << endl;
}

// Fungsi untuk menampilkan menu
void tampilkanMenu(const string& nama) {
    tampilkanHeader(nama);
    cout << "1. Konversi Huruf ke Biner" << endl;
    cout << "2. Operasi XOR antar Huruf" << endl;
    cout << "3. Ganti Nama" << endl;
    cout << "4. Exit" << endl;
    cout << "==========================================" << endl;
    cout << "Pilih menu (1-4): ";
}

int main() {
    string nama = "Default";
    int pilihan;
    char lanjut;
    
    do {
        system("cls"); // Untuk Windows, gunakan system("clear") untuk Linux/Mac
        tampilkanMenu(nama);
        cin >> pilihan;
        
        switch(pilihan) {
            case 1: {
                // Konversi Huruf ke Biner
                system("cls");
                tampilkanHeader(nama);
                cout << "=== KONVERSI HURUF KE BINER ===" << endl;
                
                string input;
                cout << "Masukkan huruf atau kata: ";
                cin.ignore();
                getline(cin, input);
                
                cout << "\nHasil Konversi:" << endl;
                cout << "Teks: " << input << endl;
                cout << "Biner: ";
                
                for (char c : input) {
                    if (isalpha(c)) {
                        string biner = hurufKeBiner(c);
                        cout << biner << " ";
                    }
                }
                cout << endl;
                
                break;
            }
            
            case 2: {
                // Operasi XOR antar Huruf
                system("cls");
                tampilkanHeader(nama);
                cout << "=== OPERASI XOR ANTAR HURUF ===" << endl;
                
                char huruf1, huruf2;
                cout << "Masukkan huruf pertama: ";
                cin >> huruf1;
                cout << "Masukkan huruf kedua: ";
                cin >> huruf2;
                
                if (isalpha(huruf1) && isalpha(huruf2)) {
                    char hasilXOR = xorHuruf(huruf1, huruf2);
                    string biner1 = hurufKeBiner(huruf1);
                    string biner2 = hurufKeBiner(huruf2);
                    string binerHasil = hurufKeBiner(hasilXOR);
                    
                    cout << "\nHasil Operasi XOR:" << endl;
                    cout << huruf1 << " (" << biner1 << ") XOR " 
                         << huruf2 << " (" << biner2 << ")" << endl;
                    cout << "Hasil: " << hasilXOR << " (" << binerHasil << ")" << endl;
                    
                    // Tampilkan tabel kebenaran
                    cout << "\nTabel Kebenaran XOR:" << endl;
                    cout << "Bit1 Bit2 Hasil" << endl;
                    for (int i = 0; i < 8; i++) {
                        cout << " " << biner1[i] << "   " << biner2[i] 
                             << "    " << binerHasil[i] << endl;
                    }
                } else {
                    cout << "Error: Input harus berupa huruf!" << endl;
                }
                
                break;
            }
            
            case 3: {
                // Ganti Nama
                system("cls");
                tampilkanHeader(nama);
                cout << "=== GANTI NAMA ===" << endl;
                
                cout << "Nama saat ini: " << nama << endl;
                cout << "Masukkan nama baru: ";
                cin.ignore();
                getline(cin, nama);
                
                cout << "Nama berhasil diubah menjadi: " << nama << endl;
                break;
            }
            
            case 4: {
                // Exit
                system("cls");
                tampilkanHeader(nama);
                cout << "Terima kasih telah menggunakan kalkulator biner!" << endl;
                cout << "Program selesai." << endl;
                return 0;
            }
            
            default: {
                cout << "Pilihan tidak valid! Silakan pilih 1-4." << endl;
                break;
            } 
        }
        
        cout << "\nKembali ke menu utama? (y/n): ";
        cin >> lanjut;
        
    } while (lanjut == 'y' || lanjut == 'Y');
    
    cout << "Terima kasih telah menggunakan kalkulator biner!" << endl;
    
    return 0;
}