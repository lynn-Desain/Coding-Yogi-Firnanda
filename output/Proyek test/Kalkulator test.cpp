#include <iostream>

using namespace std;

int main() {
    double num1, num2;
    char op;
    cout << "Kalkulator Pemrograman Sederhana\n";
    cout << "Masukkan operasi dalam format: angka1 operator angka2\n";
    cout << "Contoh: 5 + 3\n";
    cout << "Operator yang didukung: +, -, *, /\n";
    cout << "Masukkan operasi: ";
    cin >> num1 >> op >> num2;

    double result;
    bool valid = true;

    switch(op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                cout << "Error: Pembagian dengan nol tidak diperbolehkan.\n";
                valid = false;
            } else {
                result = num1 / num2;
            }
            break;
        default:
            cout << "Operator tidak dikenali.\n";
            valid = false;
    }

    if (valid) {
        cout << "Hasil: " << result << endl;
    }

    return 0;
}
