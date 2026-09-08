#include <iostream>              // Library standar untuk input-output
#include <string>                // Library string
#include <limits>                // Library numeric_limits
#include <vector>                // Library untuk array dinamis
#include <iomanip>               // Library manipulasi output tabel
#include <fstream>               // Library file
#include <cstdlib>               // Library atoi dan atof

using namespace std;

// ===== Struktur Data Mahasiswa =====
struct Mahasiswa {
    string nama;
    int jumlahHadir;
    float persentase;
    bool isLulus;
};

// ===== Fungsi Membaca Data dari File CSV =====
void bacaDataDariFile(vector<Mahasiswa> &daftar) {
    ifstream file("rekap.csv");
    if (!file) return;  // Jika file tidak ada, keluar

    string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        Mahasiswa mhs;
        string tmp;
        size_t pos = 0;

        // Nama
        pos = line.find(',');
        if (pos == string::npos) continue;
        mhs.nama = line.substr(0, pos);
        line.erase(0, pos + 1);

        // Jumlah hadir
        pos = line.find(',');
        if (pos == string::npos) continue;
        tmp = line.substr(0, pos);
        mhs.jumlahHadir = atoi(tmp.c_str());
        line.erase(0, pos + 1);

        // Persentase
        pos = line.find(',');
        if (pos == string::npos) continue;
        tmp = line.substr(0, pos);
        mhs.persentase = atof(tmp.c_str());
        line.erase(0, pos + 1);

        // Status lulus
        mhs.isLulus = (line == "1") ? true : false;

        daftar.push_back(mhs);
    }
    file.close();
}

// ===== Fungsi Menulis Semua Data ke File CSV (overwrite) =====
void tulisSemuaDataKeFile(const vector<Mahasiswa> &daftar) {
    ofstream file("rekap.csv");
    if (!file) return;

    // Tulis header
    file << "Nama Mahasiswa,Jumlah Hadir,Persentase,Lulus\n";

    for (const auto &mhs : daftar) {
        file << mhs.nama << "," 
             << mhs.jumlahHadir << "," 
             << mhs.persentase << "," 
             << (mhs.isLulus ? "1" : "0") << endl;
    }

    file.close();
}

// ===== Fungsi Menulis Data ke File CSV (append) =====
void tulisDataKeFile(const Mahasiswa &mhs) {
    bool fileBaru = false;

    ifstream cek("rekap.csv");
    if (!cek.good()) fileBaru = true; // File belum ada → baru
    cek.close();

    ofstream file("rekap.csv", ios::app);
    if (!file) return;

    if (fileBaru) {
        // Tulis header jika file baru
        file << "Nama Mahasiswa,Jumlah Hadir,Persentase,Lulus\n";
    }

    file << mhs.nama << "," 
         << mhs.jumlahHadir << "," 
         << mhs.persentase << "," 
         << (mhs.isLulus ? "1" : "0") << endl;

    file.close();
}

// ===== Fungsi Menampilkan Daftar Mahasiswa =====
void tampilkanDaftar(const vector<Mahasiswa> &daftar) {
    cout << left << setw(5) << "No"
         << setw(20) << "Nama"
         << setw(15) << "Jumlah Hadir"
         << setw(15) << "Persentase"
         << setw(10) << "Lulus" << endl;
    cout << "-------------------------------------------------------------\n";

    for (size_t i = 0; i < daftar.size(); i++) {
        const Mahasiswa &m = daftar[i];
        cout << left << setw(5) << (i + 1)
             << setw(20) << m.nama
             << setw(15) << m.jumlahHadir
             << setw(15) << fixed << setprecision(2) << m.persentase
             << (m.isLulus ? "Ya" : "Tidak") << endl;
    }
    cout << endl;
}

// ===== PROGRAM UTAMA =====
int main() {
    // ===== LOGIN =====
    string username, password;
    const string USERNAME = "Yoginanda2007";
    const string PASSWORD = "Nanda2007";
    int percobaan = 0;
    bool loginBerhasil = false;

    while (percobaan < 3 && !loginBerhasil) {
        cout << "=== HALAMAN LOGIN ===" << endl;
        cout << "Masukkan Username : "; cin >> username;
        cout << "Masukkan Password : "; cin >> password;

        if (username == USERNAME && password == PASSWORD) {
            cout << "\nLogin berhasil! Selamat datang, " << username << ".\n\n";
            loginBerhasil = true;
        } else {
            cout << "\n[ERROR] Username atau Password salah!\n\n";
            percobaan++;
        }
    }

    if (!loginBerhasil) {
        cout << "Anda sudah gagal login 3 kali. Program dihentikan.\n";
        return 0;
    }

    // ===== DATA PRESENSI =====
    vector<Mahasiswa> daftarMahasiswa;
    bacaDataDariFile(daftarMahasiswa);

    int pilihan;

    // ===== MENU UTAMA =====
    do {
        cout << "=== MENU UTAMA ===\n";
        cout << "1. Input Data Presensi\n";
        cout << "2. Lihat Rekap Presensi\n";
        cout << "3. Edit Data Presensi\n";
        cout << "4. Hapus Data Presensi\n";
        cout << "5. Keluar Program\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihan;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (pilihan == 1) {
            Mahasiswa mhs;
            cout << "\n=== Input Data Kehadiran Mahasiswa ===\n";
            cout << "Nama Mahasiswa        : ";
            getline(cin, mhs.nama);

            cout << "Jumlah Hadir (0-16)   : ";
            cin >> mhs.jumlahHadir;
            while (mhs.jumlahHadir < 0 || mhs.jumlahHadir > 16) {
                cout << "[ERROR] Jumlah hadir hanya boleh 0-16.\n";
                cout << "Masukkan ulang: ";
                cin >> mhs.jumlahHadir;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            mhs.persentase = (mhs.jumlahHadir / 16.0f) * 100;
            mhs.isLulus = (mhs.persentase >= 75);

            daftarMahasiswa.push_back(mhs);
            tulisDataKeFile(mhs);

            cout << "[INFO] Data berhasil disimpan ke rekap.csv.\n\n";

        } else if (pilihan == 2) {
            cout << "\n=== REKAP PRESENSI MAHASISWA ===\n";
            if (daftarMahasiswa.empty()) {
                cout << "Belum ada data presensi yang diinput.\n\n";
            } else {
                tampilkanDaftar(daftarMahasiswa);
            }

        } else if (pilihan == 3) {
            // Edit Data
            if (daftarMahasiswa.empty()) {
                cout << "\nBelum ada data untuk diedit.\n\n";
                continue;
            }
            cout << "\n=== Edit Data Presensi ===\n";
            tampilkanDaftar(daftarMahasiswa);
            cout << "Masukkan nomor data yang ingin diedit: ";
            int idx;
            cin >> idx;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (idx < 1 || idx > (int)daftarMahasiswa.size()) {
                cout << "[ERROR] Nomor data tidak valid.\n\n";
                continue;
            }

            Mahasiswa &mhs = daftarMahasiswa[idx - 1];
            cout << "Edit data untuk mahasiswa: " << mhs.nama << endl;

            cout << "Nama Mahasiswa (kosongkan jika tidak diubah): ";
            string inputNama;
            getline(cin, inputNama);
            if (!inputNama.empty()) {
                mhs.nama = inputNama;
            }

            cout << "Jumlah Hadir (0-16, -1 jika tidak diubah): ";
            int inputHadir;
            cin >> inputHadir;
            while ((inputHadir < -1) || (inputHadir > 16)) {
                cout << "[ERROR] Jumlah hadir hanya boleh 0-16 atau -1 untuk tidak diubah.\n";
                cout << "Masukkan ulang: ";
                cin >> inputHadir;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (inputHadir != -1) {
                mhs.jumlahHadir = inputHadir;
                mhs.persentase = (mhs.jumlahHadir / 16.0f) * 100;
                mhs.isLulus = (mhs.persentase >= 75);
            }

            tulisSemuaDataKeFile(daftarMahasiswa);
            cout << "[INFO] Data berhasil diupdate.\n\n";

        } else if (pilihan == 4) {
            // Hapus Data
            if (daftarMahasiswa.empty()) {
                cout << "\nBelum ada data untuk dihapus.\n\n";
                continue;
            }
            cout << "\n=== Hapus Data Presensi ===\n";
            tampilkanDaftar(daftarMahasiswa);
            cout << "Masukkan nomor data yang ingin dihapus: ";
            int idx;
            cin >> idx;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (idx < 1 || idx > (int)daftarMahasiswa.size()) {
                cout << "[ERROR] Nomor data tidak valid.\n\n";
                continue;
            }

            cout << "Data mahasiswa " << daftarMahasiswa[idx - 1].nama << " akan dihapus. Y/N? ";
            char konfirmasi;
            cin >> konfirmasi;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (konfirmasi == 'Y' || konfirmasi == 'y') {
                daftarMahasiswa.erase(daftarMahasiswa.begin() + idx - 1);
                tulisSemuaDataKeFile(daftarMahasiswa);
                cout << "[INFO] Data berhasil dihapus.\n\n";
            } else {
                cout << "[INFO] Penghapusan dibatalkan.\n\n";
            }

        } else if (pilihan == 5) {
            cout << "\nTerima kasih! Program selesai.\n";
        } else {
            cout << "[ERROR] Pilihan menu tidak valid.\n\n";
        }

    } while (pilihan != 5);

    return 0;
}