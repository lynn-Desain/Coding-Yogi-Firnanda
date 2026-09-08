#include <iostream>      

using namespace std;     

int main() {
        cout << "Nama         : Yogi Firnanda Saputra " << endl;
        cout << "Nim          : 2511102441170" << endl;
        cout << "Mata Kuliah  : Dasar Pemrograman" << endl;
        
    float angka1, angka2, rata_rata;   

    cout << "Nilai UTS    : "; 
    cin >> angka1;                

    cout << "Nilai UAS    : "; 
    cin >> angka2;                  

    int total = angka1 + angka2;
    rata_rata = total / 2.0;        
    
    cout << "Total Nilai     = " << total << endl;
    cout << "Nilai rata-rata = " << rata_rata << endl;  
    


    char nilai_huruf;
    if (rata_rata >= 85) {
        nilai_huruf = 'A';
    } else if (rata_rata >= 70) {
        nilai_huruf = 'B';
    } else if (rata_rata >= 55) {
        nilai_huruf = 'C';
    } else if (rata_rata >= 40) {
        nilai_huruf = 'D';
    } else {
        nilai_huruf = 'E';
    }

    cout << "Nilai Huruf     = " << nilai_huruf << endl;
    return 0;
}