#include "Library.h"
#include "Book.h"
#include "BasePerson.h"
#include "Transaction.h"
#include <iostream>

using namespace std;

Library::Library() {
    // Burada veritabanı bağlantısını ya da diğer gerekli başlangıç işlemlerini yapabilirsiniz
}

void Library::addBook(Book* book) {
    if (book != nullptr) {
        books.push_back(book);
        // Veritabanına ekleme işlemi
        // db.addBook(book);
        cout << "Kitap başarıyla eklendi." << endl;
    } else {
        cerr << "Kitap eklenemedi: Geçersiz kitap nesnesi." << endl;
    }
}

void Library::addPerson(BasePerson* person) {
    if (person != nullptr) {
        persons.push_back(person);
        // Veritabanına ekleme işlemi
        db.addMember(person->getName(), "Soyad", "şifre", "kategori"); // Örnek veriler kullanıldı
        cout << "Kişi başarıyla eklendi." << endl;
    } else {
        cerr << "Kişi eklenemedi: Geçersiz kişi nesnesi." << endl;
    }
}

void Library::executeTransaction(Transaction* t) {
    if (t != nullptr) {
        t->execute();
        transactions.push_back(t);
        cout << "İşlem başarıyla gerçekleştirildi." << endl;
    } else {
        cerr << "İşlem gerçekleştirilemedi: Geçersiz işlem nesnesi." << endl;
    }
}