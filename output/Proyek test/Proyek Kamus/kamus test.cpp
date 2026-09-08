#include <iostream>
#include <string>
#include <map>
#include <algorithm> // Untuk transform (case-insensitive)
using namespace std;

int main() {
    // Kamus Indonesia ke Inggris
    map<string, string> idToEn = {
        {"saya", "I"},
        {"kamu", "you"},
        {"dia", "he/she"},
        {"kami", "we"},
        {"mereka", "they"},
        {"makan", "eat"},
        {"minum", "drink"},
        {"tidur", "sleep"},
        {"berlari", "run"},
        {"berjalan", "walk"},
        {"melihat", "see"},
        {"mendengar", "hear"},
        {"berbicara", "speak"},
        {"menulis", "write"},
        {"membaca", "read"},
        {"rumah", "house"},
        {"sekolah", "school"},
        {"kantor", "office"},
        {"mobil", "car"},
        {"sepeda", "bicycle"},
        {"jalan", "road"},
        {"air", "water"},
        {"makanan", "food"},
        {"minuman", "drink"},
        {"teman", "friend"},
        {"keluarga", "family"},
        {"besar", "big"},
        {"kecil", "small"},
        {"panjang", "long"},
        {"pendek", "short"},
        {"cepat", "fast"},
        {"lambat", "slow"},
        {"bagus", "good"},
        {"buruk", "bad"},
        {"panas", "hot"},
        {"dingin", "cold"},
        {"indah", "beautiful"},
        {"jelek", "ugly"},
        {"mudah", "easy"},
        {"sulit", "difficult"},
        {"baru", "new"},
        {"lama", "old"},
        {"tinggi", "tall"},
        {"rendah", "low"},
        {"kaya", "rich"},
        {"miskin", "poor"},
        {"senang", "happy"},
        {"sedih", "sad"},
        {"marah", "angry"},
        {"tenang", "calm"},
        {"buku", "book"},
        {"pensil", "pencil"},
        {"meja", "table"},
        {"kursi", "chair"},
        {"jendela", "window"},
        {"pintu", "door"},
        {"langit", "sky"},
        {"matahari", "sun"},
        {"bulan", "moon"},
        {"bintang", "star"},
        {"hujan", "rain"},
        {"salju", "snow"},
        {"angin", "wind"},
        {"api", "fire"},
        {"tanah", "earth"},
        {"gunung", "mountain"},
        {"laut", "sea"},
        {"sungai", "river"},
        {"hutan", "forest"},
        {"kota", "city"},
        {"desa", "village"},
        {"pasar", "market"},
        {"toko", "shop"},
        {"rumah sakit", "hospital"},
        {"polisi", "police"},
        {"guru", "teacher"},
        {"dokter", "doctor"},
        {"perawat", "nurse"},
        {"pelajar", "student"},
        {"mahasiswa", "college student"},
        {"anak", "child"},
        {"ibu", "mother"},
        {"ayah", "father"},
        {"adik", "younger sibling"},
        {"kakak", "older sibling"},
        {"saudara", "relative"},
        {"cinta", "love"},
        {"damai", "peace"},
        {"perang", "war"},
        {"kerja", "work"},
        {"belajar", "study"},
        {"bermain", "play"},
        {"beristirahat", "rest"},
        {"berpikir", "think"},
        {"berdoa", "pray"},
        {"bernyanyi", "sing"},
        {"menari", "dance"},
        {"berfoto", "take photo"},
        {"mendengarkan", "listen"},
        {"melukis", "paint"},
        {"memasak", "cook"},
        {"membersihkan", "clean"},
        {"membeli", "buy"},
        {"menjual", "sell"},
        {"membawa", "carry"},
        {"membuka", "open"},
        {"menutup", "close"},
        {"menggambar", "draw"},
        {"melompat", "jump"},
        {"berenang", "swim"},
        {"terbang", "fly"},
        {"jatuh", "fall"},
        {"bangun", "wake up"},
        {"mencuci", "wash"},
        {"memakai", "wear"},
        {"mencium", "smell"},
        {"merasakan", "feel"},
        {"mengerti", "understand"},
        {"mengetahui", "know"},
        {"mengingat", "remember"},
        {"melupakan", "forget"},
        {"membantu", "help"},
        {"menolong", "assist"},
        {"menunggu", "wait"},
        {"bertemu", "meet"},
        {"pergi", "go"},
        {"datang", "come"},
        {"masuk", "enter"},
        {"keluar", "exit"},
        {"naik", "go up"},
        {"turun", "go down"},
        {"berhenti", "stop"},
        {"mulai", "start"},
        {"selesai", "finish"}
    };

    // Kamus Inggris ke Indonesia (kebalikan dari idToEn)
    map<string, string> enToId;
    for (const auto& pair : idToEn) {
        // Untuk menghindari overwrite jika arti sama, cek dulu
        if (enToId.find(pair.second) == enToId.end()) {
            enToId[pair.second] = pair.first;
        }
    }

    string input;
    int pilihan;

    cout << "=== Kamus Mini Bahasa Indonesia - Inggris ===" << endl;
    cout << "Pilih opsi:" << endl;
    cout << "1. Cari terjemahan Indonesia ke Inggris" << endl;
    cout << "2. Cari terjemahan Inggris ke Indonesia" << endl;
    cout << "3. Keluar" << endl;

    while (true) {
        cout << "\nMasukkan pilihan (1-3): ";
        cin >> pilihan;
        cin.ignore(); // Membersihkan buffer input

        if (pilihan == 3) {
            cout << "Terima kasih! Selamat tinggal." << endl;
            break;
        } else if (pilihan == 1 || pilihan == 2) {
            cout << "Masukkan kata yang ingin dicari: ";
            getline(cin, input);

            // Konversi input ke lowercase untuk pencarian case-insensitive (sederhana)
            transform(input.begin(), input.end(), input.begin(), ::tolower);

            map<string, string>* kamus = (pilihan == 1) ? &idToEn : &enToId;
            auto it = kamus->find(input);

            if (it != kamus->end()) {
                cout << "Terjemahan: " << it->second << endl;
            } else {
                cout << "Maaf, kata '" << input << "' tidak ditemukan dalam kamus." << endl;
            }
        } else {
            cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
    }

    return 0;
}
