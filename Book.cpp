#include "Book.h"
#include <iostream>

using namespace std;

void Book::checkout() {
    cout << "Kitap ödünç alındı: " << title << endl;
}

void Book::returnBook() {
    cout << "Kitap iade edildi: " << title << endl;
}