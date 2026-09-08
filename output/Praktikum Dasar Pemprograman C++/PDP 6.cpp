#include <iostream>    // Untuk cout, cin
#include <bitset>      // Untuk menampilkan dalam bentuk biner
#include <cmath>       // Untuk fungsi pow()
using namespace std;

// Fungsi untuk menampilkan konversi desimal ke biner manual
void tampilkanKonversi(int n) {
    cout << "\nLangkah konversi desimal " << n << " ke biner:" << endl;

    int sisa;
    string biner = "";

    int temp = n;
    while (temp > 0) {
        sisa = temp % 2;              // ambil sisa pembagian 2
        biner = to_string(sisa) + biner; // simpan bit di depan string
        cout << temp << " ÷ 2 = " << temp / 2 << " sisa " << sisa << endl;
        temp /= 2;
    }

    if (biner == "") biner = "0";     // jika input 0
    cout << "Hasil biner: " << biner << endl;
}

int main() {
    unsigned int x, y;

    cout << "=== PROGRAM PEMBELAJARAN BITWISE DAN KONVERSI BINER ===" << endl;
    cout << "Masukkan nilai x: ";
    cin >> x;
    cout << "Masukkan nilai y: ";
    cin >> y;

    // Menampilkan hasil konversi manual
    tampilkanKonversi(x);
    tampilkanKonversi(y);

    cout << "\n=== Representasi Biner Otomatis (8-bit) ===" << endl;
    cout << "x = " << bitset<8>(x) << " (" << x << ")" << endl;
    cout << "y = " << bitset<8>(y) << " (" << y << ")" << endl;
    cout << "============================================\n";

    // Operasi dasar bitwise
    cout << "x & y  = " << bitset<8>(x & y)
         << " (" << (x & y) << ") --> AND" << endl;

    cout << "x | y  = " << bitset<8>(x | y)
         << " (" << (x | y) << ") --> OR" << endl;

    cout << "x ^ y  = " << bitset<8>(x ^ y)
         << " (" << (x ^ y) << ") --> XOR" << endl;

    cout << "~x     = " << bitset<8>(~x)
         << " (" << (~x) << ") --> NOT x" << endl;

    cout << "x << 1 = " << bitset<8>(x << 1)
         << " (" << (x << 1) << ") --> Geser kiri 1 bit" << endl;

    cout << "x >> 1 = " << bitset<8>(x >> 1)
         << " (" << (x >> 1) << ") --> Geser kanan 1 bit" << endl;

    // Gabungan operasi
    unsigned int hasil = (x ^ y) << 2;
    cout << "\n(x ^ y) << 2 = " << bitset<8>(hasil)
         << " (" << hasil << ") --> XOR lalu geser kiri 2 bit" << endl;

    cout << "\n=== Analisis Bit Per Bit ===" << endl;
    cout << "x: " << bitset<8>(x) << endl;
    cout << "y: " << bitset<8>(y) << endl;
    cout << "AND (x & y):" << endl;

    // Tampilkan analisis per bit
    bitset<8> bx(x), by(y), band(x & y);
    for (int i = 7; i >= 0; i--) {
        cout << "Bit ke-" << (7 - i) << ": " 
             << bx[i] << " & " << by[i] << " = " << band[i] << endl;
    }

    cout << "\nProgram selesai." << endl;
    return 0;
}