#include "Library.h"
#include "Book.h"
#include "BasePerson.h"
#include "Transaction.h"
#include <iostream>

using namespace std;

Library::Library() {
}

void Library::addBook(Book* book) {
    if (book != nullptr) {
        books.push_back(book);
        // Veritabanına ekleme işlemi
        db.addBook(book->getTitle(), book->getAuthor(), book->getISBN(), "", "", "", "", true);
        cout << "Kitap başarıyla eklendi." << endl;
    } else {
        cerr << "Kitap eklenemedi: Geçersiz kitap nesnesi." << endl;
    }
}

void Library::addPerson(BasePerson* person) {
    if (person != nullptr) {
        persons.push_back(person);
        // Veritabanına ekleme işlemi
        db.addMember(person->getName(), "Soyad", "şifre", "kategori");
        cout << "Kişi başarıyla eklendi." << endl;
    } else {
        cerr << "Kişi eklenemedi: Geçersiz kişi nesnesi." << endl;
    }
}

void Library::executeTransaction(Transaction* t) {
    if (t != nullptr) {
        vector<vector<string>> availableBooks = db.listAvailableBooks();
        
        if (availableBooks.empty()) {
            cout << "Mevcut ödünç alınabilir kitap yok." << endl;
            return;
        }

        cout << "Mevcut ödünç alınabilir kitaplar:" << endl;
        for (const auto& book : availableBooks) {
            cout << "Başlık: " << book[0] << ", Yazar: " << book[1] << ", ISBN: " << book[2] << endl;
        }

        cout << "Ödünç almak istediğiniz kitabın ISBN numarasını girin: ";
        string isbn;
        cin >> isbn;

        db.updateBookAvailability(isbn, false);
        t->execute();
        
        transactions.push_back(t);
        cout << "İşlem başarıyla gerçekleştirildi." << endl;
    } else {
        cerr << "İşlem gerçekleştirilemedi: Geçersiz işlem nesnesi." << endl;
    }
}