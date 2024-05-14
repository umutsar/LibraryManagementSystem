#include "Book.h"
#include <iostream>

using namespace std;

void Book::checkout() {
    // Ödünç alma işlemleri
    cout << "Kitap ödünç alındı: " << title << endl;
}

void Book::returnBook() {
    // İade işlemleri
    cout << "Kitap iade edildi: " << title << endl;
}