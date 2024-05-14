#include "Librarian.h"
#include "Book.h"
#include "BasePerson.h"
#include <iostream>

using namespace std;

void Librarian::manageBooks(Book* book) {
    if (book != nullptr) {
        // Kitap yönetim işlemleri
        cout << "Kitap başarıyla yönetildi: " << book->getTitle() << endl;
    } else {
        cerr << "Kitap yönetimi başarısız: Geçersiz kitap nesnesi." << endl;
    }
}

void Librarian::managePersons(BasePerson* person) {
    if (person != nullptr) {
        // Kişi yönetim işlemleri
        cout << "Kişi başarıyla yönetildi: " << person->getName() << endl;
    } else {
        cerr << "Kişi yönetimi başarısız: Geçersiz kişi nesnesi." << endl;
    }
}