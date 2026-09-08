#include <iostream>
#include <string>
#include <iomanip>  // Untuk formatting output

using namespace std;

// Struct untuk data mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    string kehadiran;  // "Hadir", "Absen", atau "Tidak Hadir"
};

int main() {
    int jumlahMahasiswa;
    
    // Input jumlah mahasiswa
    cout << "Masukkan jumlah mahasiswa: ";
    cin >> jumlahMahasiswa;
    cin.ignore();  // Membersihkan buffer input setelah cin
    
    // Array untuk menyimpan data mahasiswa
    Mahasiswa dataMahasiswa[100];  // Asumsi maksimal 100 mahasiswa
    int totalHadir = 0;
    
    // Loop untuk input data setiap mahasiswa/
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << "\n--- Data Mahasiswa ke-" << (i + 1) << " ---" << endl;
        
        cout << "Nama: ";
        getline(cin, dataMahasiswa[i].nama);
        
        cout << "NIM: ";
        cin >> dataMahasiswa[i].nim;
        cin.ignore();  // Membersihkan buffer setelah cin
        
        cout << "Status Kehadiran (Hadir/Absen/Tidak Hadir): ";
        getline(cin, dataMahasiswa[i].kehadiran);
        
        // Hitung total hadir (case-insensitive)
        if (dataMahasiswa[i].kehadiran == "Hadir" || 
            dataMahasiswa[i].kehadiran == "hadir") {
            totalHadir++;
        }
    }
    
    // Tampilkan ringkasan data
    cout << "\n=== DATA KEHADIRAN MAHASISWA ===" << endl;
    cout << left << setw(5) << "No" << setw(20) << "Nama" << setw(15) << "NIM" << setw(15) << "Kehadiran" << endl;
    cout << string(55, '-') << endl;
    
    for (int i = 0; i < jumlahMahasiswa; i++) {
        cout << left << setw(5) << (i + 1) 
            << setw(20) << dataMahasiswa[i].nama 
            << setw(15) << dataMahasiswa[i].nim 
            << setw(15) << dataMahasiswa[i].kehadiran << endl;
    }
    
    // Statistik
    double persentaseHadir = (static_cast<double>(totalHadir) / jumlahMahasiswa) * 100;
    cout << "\nTotal Mahasiswa: " << jumlahMahasiswa << endl;
    cout << "Total Hadir: " << totalHadir << endl;
    cout << "Persentase Hadir: " << fixed << setprecision(2) << persentaseHadir << "%" << endl;
    
    return 0;
}
