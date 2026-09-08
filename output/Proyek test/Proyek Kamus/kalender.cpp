#include <iostream>
#include <string>
#include <iomanip>  // Untuk formatting tanggal (setw, setfill)
using namespace std;

// Struktur untuk menyimpan agenda
struct Agenda {
    string tanggal;
    string kegiatan;
};

// Fungsi untuk mengecek apakah tanggal memiliki agenda
bool punyaAgenda(const Agenda daftar[], int jumlahAgenda, int hari, int bulan, int tahun) {
    stringstream ss;
    ss << setfill('0') << setw(2) << hari << "/" 
       << setfill('0') << setw(2) << bulan << "/" 
       << tahun;
    string tanggalCari = ss.str();
    
    for (int i = 0; i < jumlahAgenda; i++) {
        if (daftar[i].tanggal == tanggalCari) {
            return true;
        }
    }
    return false;
}

// Fungsi untuk menampilkan kalender bulan dengan penanda agenda
void tampilkanKalender(Agenda daftar[], int jumlahAgenda) {
    int bulan, tahun;
    int hari_pertama, jumlah_hari;

    cout << "Masukkan tahun: ";
    cin >> tahun;
    cout << endl;
    
    cout << "Masukkan bulan: ";
    cin >> bulan;
    cout << endl;

    cout << "Masukkan hari pertama sesuai tahun yang di input (1 = minggu, 2 = senin, dst.): ";
    cin >> hari_pertama;

    // Hitung jumlah hari dalam bulan
    switch (bulan) {
        case 2:
            if ((tahun % 400 == 0) || (tahun % 4 == 0 && tahun % 100 != 0))
                jumlah_hari = 29;
            else
                jumlah_hari = 28;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            jumlah_hari = 30;
            break;
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            jumlah_hari = 31;
            break;
        default:
            cout << "Bulan tidak valid!" << endl;
            return;
    }

    cout << endl << "Mingg\tSen\tSel\tRab\tKam\tJum\tSab\n";

    // Menampilkan tab kosong sampai hari pertama
    for (int i = 1; i < hari_pertama; i++) {
        cout << "\t";
    }

    // Menampilkan angka-angka hari dengan penanda agenda
    for (int j = 1; j <= jumlah_hari; j++) {
        if (((j + hari_pertama - 2) % 7 == 0) && (j != 1))
            cout << endl;
        
        cout << j;
        if (punyaAgenda(daftar, jumlahAgenda, j, bulan, tahun)) {
            cout << "*";  // Penanda untuk tanggal dengan kegiatan (seperti "merah" atau highlight)
        }
        cout << "\t";
    }
    
    cout << endl << endl;
    cout << "Catatan: * menandakan tanggal dengan kegiatan/agenda." << endl;
}

int main() {
    Agenda daftar[100];  // Maksimal 100 jadwal
    int jumlahAgenda = 0;
    int pilihan;
    string cariTanggal;

    do {
        cout << "\n=== Aplikasi Kalender & Agenda Harian ===\n";
        cout << "1. Input Jadwal Kegiatan\n";
        cout << "2. Tampilkan Agenda per Tanggal\n";
        cout << "3. Tampilkan Kalender Bulan (dengan penanda kegiatan)\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu (1-4): ";
        cin >> pilihan;
        cin.ignore(); // Bersihkan buffer agar getline bisa dipakai

        switch (pilihan) {
            case 1:
                if (jumlahAgenda < 100) {
                    cout << "\nMasukkan tanggal (dd/mm/yyyy): ";
                    getline(cin, daftar[jumlahAgenda].tanggal);
                    cout << "Masukkan kegiatan: ";
                    getline(cin, daftar[jumlahAgenda].kegiatan);
                    jumlahAgenda++;
                    cout << "✅ Jadwal berhasil ditambahkan!\n";
                } else {
                    cout << "❌ Kapasitas agenda penuh!\n";
                }
                break;

            case 2:
                cout << "\nMasukkan tanggal yang ingin dicari (dd/mm/yyyy): ";
                getline(cin, cariTanggal);
                cout << "\nAgenda pada tanggal " << cariTanggal << ":\n";
                {
                    bool ada = false;
                    for (int i = 0; i < jumlahAgenda; i++) {
                        if (daftar[i].tanggal == cariTanggal) {
                            cout << "- " << daftar[i].kegiatan << endl;
                            ada = true;
                        }
                    }
                    if (!ada) {
                        cout << "❌ Tidak ada agenda pada tanggal tersebut.\n";
                    }
                }
                break;

            case 3:
                tampilkanKalender(daftar, jumlahAgenda);
                break;

            case 4:
                cout << "Terima kasih! Program selesai.\n";
                break;

            default:
                cout << "⚠ Pilihan tidak valid!\n";
        }

    } while (pilihan != 4);

    return 0;
}

