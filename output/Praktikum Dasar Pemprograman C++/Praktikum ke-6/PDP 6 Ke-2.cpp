#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <limits> // Diperlukan untuk std::numeric_limits

using namespace std;

// Fungsi untuk mengonversi nilai desimal (ASCII) ke string biner 8-bit
string decToBinary(int dec) {
    return bitset<8>(dec).to_string();
}

// Fungsi utama untuk menampilkan operasi bitwise
void performBitwiseOperations(const string& name) {
    if (name.length() < 2) {
        cout << "\nNama harus memiliki minimal 2 karakter untuk operasi Bitwise biner." << endl;
        return;
    }

    // Ambil dua karakter pertama
    char char1 = name[0];
    char char2 = name[1];
    
    // Dapatkan nilai ASCII (desimal) dari kedua karakter
    int val1 = (int)char1; // Contoh: 'M' = 77
    int val2 = (int)char2; // Contoh: 'a' = 97

    cout << "\n----------------------------------------------------" << endl;
    cout << "OPERASI BITWISE (MENGGUNAKAN 2 KARAKTER PERTAMA: '" << char1 << "' & '" << char2 << "')" << endl;
    cout << "Nilai ASCII: " << char1 << "=" << val1 << " | " << char2 << "=" << val2 << endl;
    cout << "Nilai Biner: " << decToBinary(val1) << " | " << decToBinary(val2) << endl;
    cout << "----------------------------------------------------" << endl;

    // 1. XOR (Exclusive OR)
    int xorResult = val1 ^ val2;
    cout << "XOR antar huruf: (" << decToBinary(val1) << " ^ " << decToBinary(val2) << ") = " 
         << decToBinary(xorResult) << " (ASCII: " << xorResult << ", Char: " << (char)xorResult << ")" << endl;

    // 2. AND
    int andResult = val1 & val2;
    cout << "AND antar huruf: (" << decToBinary(val1) << " & " << decToBinary(val2) << ") = " 
         << decToBinary(andResult) << " (ASCII: " << andResult << ", Char: " << (char)andResult << ")" << endl;

    // 3. OR
    int orResult = val1 | val2;
    cout << "OR antar huruf: (" << decToBinary(val1) << " | " << decToBinary(val2) << ") = " 
         << decToBinary(orResult) << " (ASCII: " << orResult << ", Char: " << (char)orResult << ")" << endl;
    
    cout << "----------------------------------------------------" << endl;
    cout << "OPERASI UNARY (MENGGUNAKAN KARAKTER PERTAMA: '" << char1 << "')" << endl;
    cout << "----------------------------------------------------" << endl;

    // 4. NOT (Inversi Bit)
    // Catatan: NOT (~) pada int biasanya membalik semua 32-bit. Kita akan membatasi ke 8-bit saja
    int notMasked = (~val1) & 0xFF; // 0xFF (11111111) memastikan kita hanya melihat 8 bit paling bawah
    cout << "NOT setiap huruf: (~" << decToBinary(val1) << ") = " 
         << decToBinary(notMasked) << " (ASCII: " << notMasked << ", Char: " << (char)notMasked << ")" << endl;
    
    // 5. LEFT SHIFT (Geser Kiri 1 bit)
    int leftShift = val1 << 1;
    cout << "LEFT SHIFT (1): (" << decToBinary(val1) << " << 1) = " 
         << decToBinary(leftShift) << " (ASCII: " << leftShift << ", Char: " << (char)leftShift << ")" << endl;

    // 6. RIGHT SHIFT (Geser Kanan 1 bit)
    int rightShift = val1 >> 1;
    cout << "RIGHT SHIFT (1): (" << decToBinary(val1) << " >> 1) = " 
         << decToBinary(rightShift) << " (ASCII: " << rightShift << ", Char: " << (char)rightShift << ")" << endl;
}

// Fungsi untuk mengkonversi Teks ke Biner
string textToBinary(const string& text) {
    string binaryResult = "";
    for (char character : text) {
        binaryResult += decToBinary((int)character);
        binaryResult += " ";
    }
    if (!binaryResult.empty()) binaryResult.pop_back(); 
    return binaryResult;
}

int main() {
    string currentName = "Contoh Nama"; // Nama default
    int choice;
    char repeatChoice;

    do {
        cout << "\n=======================================" << endl;
        cout << " MENU KALKULATOR BITWISE NAMA: " << currentName << endl;
        cout << "=======================================" << endl;
        cout << "1. Konversi Teks ke Biner (Seluruh Nama)" << endl;
        cout << "2. Operasi Bitwise (XOR, AND, OR, NOT, SHIFT)" << endl;
        cout << "3. Ganti Nama (" << currentName << ")" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Anda (1-4): ";
        
        if (!(cin >> choice)) {
            // Tangani input non-angka
            cout << "\nInput tidak valid. Silakan coba lagi." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // Membersihkan buffer sebelum getline
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (choice) {
            case 1: {
                cout << "\n--- Konversi Teks ke Biner ---" << endl;
                cout << "Nama: " << currentName << endl;
                cout << "Biner: " << textToBinary(currentName) << endl;
                break;
            }
            case 2: {
                performBitwiseOperations(currentName);
                break;
            }
            case 3: {
                cout << "\n--- Ganti Nama ---" << endl;
                cout << "Masukkan nama baru: ";
                getline(cin, currentName);
                cout << "Nama berhasil diganti menjadi: " << currentName << endl;
                break;
            }
            case 4:
                cout << "\nProgram selesai. Sampai jumpa!" << endl;
                return 0;
            default:
                cout << "\nPilihan tidak valid. Silakan pilih 1, 2, 3, atau 4." << endl;
        }
        
        // Tanya apakah ingin mengulang
        cout << "\n---------------------------------------" << endl;
        cout << "Lakukan operasi lain? (y/n): ";
        cin >> repeatChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        
    } while (tolower(repeatChoice) == 'y'); 

    cout << "\nProgram selesai. Terima kasih!" << endl;
    
    return 0;
}