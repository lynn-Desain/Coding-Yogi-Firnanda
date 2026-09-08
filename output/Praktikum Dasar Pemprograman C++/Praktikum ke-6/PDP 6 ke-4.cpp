#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <limits> 

using namespace std;
// --- FUNGSI UTILITY ---

// Konversi desimal (ASCII) ke string biner 8-bit
string decToBinary(int dec) {
    return bitset<8>(dec).to_string();
}

// Konversi Teks ke Biner - VERSI RANGKAIAN
string textToBinaryRangkaian(const string& text) {
    string binaryResult = "";
    for (char character : text) {
        binaryResult += decToBinary((int)character);
        binaryResult += " ";
    }
    if (!binaryResult.empty()) binaryResult.pop_back(); 
    return binaryResult;
}

// Konversi Teks ke Biner - VERSI PER ABJAD
void textToBinaryPerAbjad(const string& text) {
    cout << "\n--- Hasil Biner Per Abjad ---" << endl;
    for (char character : text) {
        cout << "'" << character << "' = " << decToBinary((int)character) << endl;
    }
}

// --- FUNGSI SUBMENU BITWISE ---

void performBitwiseOperation(const string& name, int operationChoice) {
    if (name.empty()) {
        cout << "\nPeringatan: Nama tidak boleh kosong." << endl;
        return;
    }

    char char1 = name[0];
    int val1 = (int)char1;
    
    // Operasi Biner (membutuhkan dua karakter)
    if (operationChoice >= 1 && operationChoice <= 3) {
        if (name.length() < 2) {
            cout << "\nPeringatan: Operasi ini membutuhkan minimal 2 karakter." << endl;
            return;
        }
        char char2 = name[1];
        int val2 = (int)char2;
        
        cout << "\n--- Operasi pada '" << char1 << "' (" << decToBinary(val1) << ") dan '" << char2 << "' (" << decToBinary(val2) << ") ---" << endl;
        
        int result = 0;
        string opSymbol = "";
        
        switch (operationChoice) {
            case 1: // XOR
                result = val1 ^ val2;
                opSymbol = "XOR (^)";
                break;
            case 2: // AND
                result = val1 & val2;
                opSymbol = "AND (&)";
                break;
            case 3: // OR
                result = val1 | val2;
                opSymbol = "OR (|)";
                break;
        }
        
        cout << opSymbol << " Hasil Biner: " << decToBinary(result) 
             << " | ASCII: " << result 
             << " | Karakter: " << (char)result << endl;
             
    } 
    // Operasi Unary (membutuhkan satu karakter)
    else if (operationChoice >= 4 && operationChoice <= 6) {
        cout << "\n--- Operasi pada '" << char1 << "' (" << decToBinary(val1) << ") ---" << endl;

        int result = 0;
        string opSymbol = "";
        
        switch (operationChoice) {
            case 4: // NOT
                result = (~val1) & 0xFF; // Masking untuk 8-bit
                opSymbol = "NOT (~)";
                break;
            case 5: // LEFT SHIFT
                result = val1 << 1;
                opSymbol = "LEFT SHIFT (<< 1)";
                break;
            case 6: // RIGHT SHIFT
                result = val1 >> 1;
                opSymbol = "RIGHT SHIFT (>> 1)";
                break;
        }
        
        cout << opSymbol << " Hasil Biner: " << decToBinary(result) 
             << " | ASCII: " << result 
             << " | Karakter: " << (char)result << endl;
    }
}

// --- FUNGSI MENU UTAMA ---

int main() {
    int choice;
    char repeatChoice;

    do {
        cout << "\n=======================================" << endl;
        cout << " MENU KALKULATOR BINER & BITWISE" << endl;
        cout << "=======================================" << endl;
        cout << "1. Konversi Huruf ke Biner (Masukkan Nama)" << endl;
        cout << "2. Operasi Bitwise (Masukkan Nama)" << endl;
        cout << "3. Keluar" << endl; // Opsi 3 adalah Keluar
        cout << "Pilihan Anda (1-3): ";
        
        if (!(cin >> choice)) {
            cout << "\nInput tidak valid. Silakan coba lagi." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Membersihkan buffer

        switch (choice) {
            case 1: {
                string tempName;
                cout << "\n--- Konversi Teks ke Biner ---" << endl;
                cout << "Masukkan nama/teks yang ingin dikonversi: ";
                getline(cin, tempName); 
                
                if (!tempName.empty()) {
                    // VERSI RANGKAIAN
                    cout << "\nNama: " << tempName << endl;
                    cout << "Biner (Rangkaian): " << textToBinaryRangkaian(tempName) << endl;

                    // VERSI PER ABJAD (BARU)
                    textToBinaryPerAbjad(tempName);
                } else {
                     cout << "Peringatan: Input nama tidak boleh kosong!" << endl;
                }
                break;
            }
            case 2: {
                string bitwiseName;
                cout << "\n--- OPERASI BITWISE ---" << endl;
                cout << "Masukkan nama yang akan digunakan untuk operasi Bitwise: ";
                getline(cin, bitwiseName);

                if (bitwiseName.empty()) {
                    cout << "Peringatan: Nama tidak boleh kosong!" << endl;
                    break;
                }
                
                int bitwiseChoice;
                do {
                    cout << "\n--- SUBMENU OPERASI BITWISE ---" << endl;
                    cout << "Nama yang digunakan: " << bitwiseName << endl;
                    cout << "Operasi pada Biner Karakter Pertama ('" << bitwiseName[0] << "')" << endl;
                    cout << "1. XOR antar huruf (karakter 1 & 2)" << endl;
                    cout << "2. AND antar huruf (karakter 1 & 2)" << endl;
                    cout << "3. OR antar huruf (karakter 1 & 2)" << endl;
                    cout << "4. NOT setiap huruf (karakter ke-1)" << endl;
                    cout << "5. LEFT SHIFT setiap huruf (karakter ke-1)" << endl;
                    cout << "6. RIGHT SHIFT setiap huruf (karakter ke-1)" << endl;
                    cout << "7. Kembali ke Menu Utama" << endl;
                    cout << "Pilihan Operasi (1-7): ";
                    
                    if (!(cin >> bitwiseChoice)) {
                        cout << "\nInput tidak valid. Silakan coba lagi." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    if (bitwiseChoice >= 1 && bitwiseChoice <= 6) {
                        performBitwiseOperation(bitwiseName, bitwiseChoice); 
                    }
                    
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                } while (bitwiseChoice != 7);
                break;
            }
            case 3:
                cout << "\nProgram selesai. Sampai jumpa!" << endl;
                return 0;
            default:
                cout << "\nPilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
        
        // Tanya apakah ingin mengulang
        if (choice != 3) {
             cout << "\n---------------------------------------" << endl;
             cout << "Lakukan operasi menu utama lain? (y/n): ";
             cin >> repeatChoice;
             cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        } else {
            repeatChoice = 'n';
        }
        
    } while (tolower(repeatChoice) == 'y'); 

    cout << "\nProgram selesai. Terima kasih!" << endl;
    
    return 0;
}