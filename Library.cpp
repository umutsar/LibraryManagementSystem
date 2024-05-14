#include "Library.h"
#include "Book.h"
#include "BasePerson.h"
#include "Transaction.h"
#include <iostream>

Library::Library() {
    // Burada veritabanı bağlantısını ya da diğer gerekli başlangıç işlemlerini yapabilirsiniz
}

void Library::addBook(Book* book) {
    if (book != nullptr) {
        books.push_back(book);
        // Veritabanına ekleme işlemi
        db.addBook(book->getTitle(), book->getAuthor(), book->getISBN(), "", "", "", "", true); // Örnek verilerle çağrı
        std::cout << "Kitap başarıyla eklendi." << std::endl;
    } else {
        std::cerr << "Kitap eklenemedi: Geçersiz kitap nesnesi." << std::endl;
    }
}

void Library::addPerson(BasePerson* person) {
    if (person != nullptr) {
        persons.push_back(person);
        // Veritabanına ekleme işlemi
        db.addMember(person->getName(), "Soyad", "şifre", "kategori"); // Örnek veriler kullanıldı
        std::cout << "Kişi başarıyla eklendi." << std::endl;
    } else {
        std::cerr << "Kişi eklenemedi: Geçersiz kişi nesnesi." << std::endl;
    }
}

void Library::executeTransaction(Transaction* t) {
    if (t != nullptr) {
        t->execute();
        transactions.push_back(t);
        std::cout << "İşlem başarıyla gerçekleştirildi." << std::endl;
    } else {
        std::cerr << "İşlem gerçekleştirilemedi: Geçersiz işlem nesnesi." << std::endl;
    }
}