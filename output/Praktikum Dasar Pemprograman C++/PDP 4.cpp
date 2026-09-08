#include <iostream>              // Library standar untuk input-output (cout, cin)
#include <string>                // Library untuk tipe data string (teks)
#include <limits>                // Library untuk numeric_limits (membersihkan buffer input)
#include <iomanip>               // Library untuk formatting output (tabel)
#include <vector>                // Library untuk dynamic array

using namespace std;             // Supaya tidak perlu menulis std:: di depan fungsi

// Struct untuk menyimpan data mahasiswa
struct Mahasiswa {
    string nama;
    int jumlahHadir;
    float persentaseHadir;
    string statusLulus;
};

int main() {                     // Fungsi utama program
    // ===== Deklarasi Variabel =====
    string nama;                  // << tipe data: string → untuk teks/nama lengkap
    int jumlahHadir;             // << tipe data: int → untuk bilangan bulat (0–16 kehadiran)
    float persentaseHadir;      // << tipe data: float → untuk angka desimal (persentase 0.0–100.0)
    bool isLulusKehadiran;     // << tipe data: bool → hanya bisa bernilai true/false
    char ulang;               // << tipe data: char → hanya 1 karakter (Y/N)
    
    // Vector untuk menyimpan semua data mahasiswa
    vector<Mahasiswa> dataMahasiswa;

    do { // Perulangan supaya bisa input data lebih dari sekali
        // ===== Input Nama Mahasiswa =====
        cout << "=== Input Data Kehadiran Mahasiswa ===" << endl;   // Tampilkan judul input
        cout << "Nama Mahasiswa        : ";                         // Minta user masukkan nama
        
        if (cin.peek() == '\n') {                                   // Jika ada newline sisa di buffer
            cin.ignore();                                           // Hapus newline sisa agar tidak mengganggu getline
        }
        
        getline(cin, nama);      // Input nama lengkap mahasiswa (bisa lebih dari satu kata)

        // ===== Input Jumlah Kehadiran dengan Validasi =====
        cout << "Jumlah kehadiran (pertemuan) : ";  // Minta input jumlah hadir
        cin >> jumlahHadir;                        // Simpan ke variabel jumlahHadir

        // <<< bersihkan sisa newline agar tidak mengganggu input berikutnya
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hapus semua karakter sisa di buffer sampai newline

        while (jumlahHadir < 0 || jumlahHadir > 16) {        // Validasi: jumlah hadir harus 0–16
            cout << "\n[ERROR] Salah input! Jumlah kehadiran hanya boleh 0 - 16 pertemuan.\n"; 
            cout << "Masukkan ulang jumlah kehadiran (0-16): ";   // Minta input ulang
            cin >> jumlahHadir;                                  // Input ulang jumlah hadir

            // <<< bersihkan buffer setiap input ulang
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hapus karakter sisa di buffer
        }

        // ===== Proses Hitung Persentase Kehadiran =====
        persentaseHadir = (jumlahHadir / 16.0) * 100;   // Hitung persentase kehadiran (rumus: hadir/total*100)

        // ===== Tentukan Lulus/Tidak Berdasarkan Persentase =====
        isLulusKehadiran = (persentaseHadir >= 75);    // Jika persentase >= 75% maka lulus
        string statusLulus = (isLulusKehadiran ? "Lulus" : "Tidak Lulus");

        // ===== Simpan Data ke Vector =====
        Mahasiswa mhs;
        mhs.nama = nama;
        mhs.jumlahHadir = jumlahHadir;
        mhs.persentaseHadir = persentaseHadir;
        mhs.statusLulus = statusLulus;
        dataMahasiswa.push_back(mhs);

        // ===== Output Rekap Kehadiran =====
        cout << "\n=== Rekap Kehadiran ===" << endl;   // Judul output
        cout << "Nama Mahasiswa   : " << nama << endl; // Tampilkan nama mahasiswa
        cout << "Jumlah Hadir     : " << jumlahHadir << " dari 16 pertemuan" << endl; // Jumlah hadir
        cout << "Persentase Hadir : " << fixed << setprecision(2) << persentaseHadir << "%" << endl; // Persentase hadir
        cout << "Lulus Kehadiran  : " << statusLulus << endl; // Status lulus atau tidak

        // ===== Tanya User Apakah Ingin Input Lagi =====
        bool inputValid = false;
        
        do {
            cout << "\nApakah ingin input data lagi? (Y/N): "; // Tampilkan pilihan
            cin >> ulang;                                     // Simpan jawaban ke variabel ulang

            // <<< bersihkan newline agar loop berikutnya aman
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Hapus karakter sisa di buffer

            // Validasi input: jika bukan Y/y/N/n, maka ulangi pertanyaan
            if (ulang == 'Y' || ulang == 'y' || ulang == 'N' || ulang == 'n') {
                inputValid = true;  // Input valid, keluar dari loop validasi
            } else {
                cout << "[Peringatan] Input tidak dikenali. Program akan melanjutkan..." << endl;
                cout << "Silakan masukkan Y untuk lanjut atau N untuk berhenti." << endl;
                // Tetap lanjut program meskipun input tidak valid
                inputValid = true;  // Tetap lanjut meskipun input tidak sesuai
                ulang = 'Y';       // Set default ke 'Y' agar program lanjut
            }

        } while (!inputValid);  // Ulangi sampai input valid

        cout << endl; // Tambahkan baris kosong untuk pemisah

    } while (ulang == 'Y' || ulang == 'y');   // Ulangi jika user mengetik Y/y

    // ===== TAMPILKAN TABEL SETELAH SELESAI INPUT =====
    cout << "\n" << string(70, '=') << endl;
    cout << "                       TABEL REKAP KEHADIRAN MAHASISWA" << endl;
    cout << string(70, '=') << endl;
    
    // Header tabel
    cout << left << setw(5) << "No" 
        << setw(25) << "Nama Mahasiswa" 
        << setw(15) << "Jumlah Hadir" 
        << setw(20) << "Persentase (%)" 
        << setw(15) << "Status" << endl;
    cout << string(70, '-') << endl;
    
    // Isi tabel
    for (int i = 0; i < dataMahasiswa.size(); i++) {
        cout << left << setw(5) << (i + 1) 
            << setw(25) << dataMahasiswa[i].nama 
            << setw(15) << dataMahasiswa[i].jumlahHadir 
            << setw(20) << fixed << setprecision(2) << dataMahasiswa[i].persentaseHadir 
            << setw(15) << dataMahasiswa[i].statusLulus << endl;
    }
    
    cout << string(70, '=') << endl;
    
    // ===== STATISTIK KESELURUHAN =====
    if (!dataMahasiswa.empty()) {
        int totalMahasiswa = dataMahasiswa.size();
        int totalLulus = 0;
        float totalPersentase = 0;
        
        for (const auto& mhs : dataMahasiswa) {
            if (mhs.statusLulus == "Lulus") {
                totalLulus++;
            }
            totalPersentase += mhs.persentaseHadir;
        }
        
        float rataRataPersentase = totalPersentase / totalMahasiswa;
        
        cout << "\n=== STATISTIK KESELURUHAN ===" << endl;
        cout << "Total Mahasiswa     : " << totalMahasiswa << " orang" << endl;
        cout << "Total Lulus         : " << totalLulus << " orang" << endl;
        cout << "Total Tidak Lulus   : " << (totalMahasiswa - totalLulus) << " orang" << endl;
        cout << "Rata-rata Kehadiran : " << fixed << setprecision(2) << rataRataPersentase << "%" << endl;
        
        // Persentase kelulusan
        float persentaseKelulusan = (static_cast<float>(totalLulus) / totalMahasiswa) * 100;
        cout << "Persentase Kelulusan: " << fixed << setprecision(2) << persentaseKelulusan << "%" << endl;
    }

    cout << "\nProgram selesai. Terima kasih!" << endl;  // Pesan akhir
    return 0;                                          // Selesai, kembalikan 0 (program sukses)
}