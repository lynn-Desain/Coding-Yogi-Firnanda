#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <sstream> // untuk istringstream
using namespace std;

// Fungsi untuk mengubah string menjadi lowercase
string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Fungsi untuk menerjemahkan kalimat per kata
string terjemahkanKalimat(const string& kalimat, const map<string, string>& kamus) {
    istringstream iss(kalimat);
    string kata;
    string hasil = "";
    while (iss >> kata) {
        string kataLower = toLower(kata);
        auto it = kamus.find(kataLower);
        if (it != kamus.end()) {
            hasil += it->second;
        } else {
            // Jika kata tidak ditemukan, tampilkan kata asli
            hasil += kata;
        }
        hasil += " ";
    }
    if (!hasil.empty()) {
        hasil.pop_back(); // hapus spasi terakhir
    }
    return hasil;
}

int main() {
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
        {"jalan", "street"},
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
        {"teman", "friend"},
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
        {"berbicara", "talk"},
        {"mendengarkan", "listen"},
        {"melukis", "paint"},
        {"memasak", "cook"},
        {"membersihkan", "clean"},
        {"membeli", "buy"},
        {"menjual", "sell"},
        {"membawa", "carry"},
        {"membuka", "open"},
        {"menutup", "close"},
        {"membaca", "read"},
        {"menulis", "write"},
        {"menggambar", "draw"},
        {"berlari", "run"},
        {"berjalan", "walk"},
        {"melompat", "jump"},
        {"berenang", "swim"},
        {"terbang", "fly"},
        {"jatuh", "fall"},
        {"bangun", "wake up"},
        {"tidur", "sleep"},
        {"mencuci", "wash"},
        {"memakai", "wear"},
        {"mencium", "smell"},
        {"merasakan", "feel"},
        {"melihat", "see"},
        {"mendengar", "hear"},
        {"berbicara", "speak"},
        {"berpikir", "think"},
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
        {"selesai", "finish"},
        {"bekerja", "work"},
        {"bermain", "play"},
        {"belajar", "study"},
        {"beristirahat", "rest"},
        {"berjalan", "walk"},
        {"berlari", "run"},
        {"melompat", "jump"},
        {"berenang", "swim"},
        {"terbang", "fly"},
        {"makan", "eat"},
        {"minum", "drink"},
        {"tidur", "sleep"},
        {"bangun", "wake up"},
        {"membaca", "read"},
        {"menulis", "write"},
        {"melihat", "see"},
        {"mendengar", "hear"},
        {"berbicara", "speak"},
        {"berpikir", "think"},
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

    int pilihan;
    string input;

    cout << "=== Kamus Mini Bahasa Indonesia - Inggris ===" << endl;
    cout << "Pilih opsi:" << endl;
    cout << "1. Cari terjemahan kata" << endl;
    cout << "2. Terjemahkan kalimat" << endl;
    cout << "3. Keluar" << endl;

    while (true) {
        cout << "\nMasukkan pilihan (1-3): ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == 3) {
            cout << "Terima kasih! Selamat tinggal." << endl;
            break;
        } else if (pilihan == 1) {
            cout << "Masukkan kata yang ingin dicari: ";
            getline(cin, input);
            string kataLower = toLower(input);
            auto it = idToEn.find(kataLower);
            if (it != idToEn.end()) {
                cout << "Terjemahan: " << it->second << endl;
            } else {
                cout << "Maaf, kata '" << input << "' tidak ditemukan dalam kamus." << endl;
            }
        } else if (pilihan == 2) {
            cout << "Masukkan kalimat Bahasa Indonesia: ";
            getline(cin, input);
            string hasil = terjemahkanKalimat(input, idToEn);
            cout << "Terjemahan: " << hasil << endl;
        } else {
            cout << "Pilihan tidak valid. Silakan pilih 1, 2, atau 3." << endl;
        }
    }

    return 0;
}
