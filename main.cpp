#include <iostream>
#include "Library.h"
#include "Librarian.h"
#include "Book.h"
#include "Magazine.h"
#include "Novel.h"
#include "HistoryBook.h"
#include "Student.h"
#include "AcademicStaff.h"
#include "Borrow.h"
#include "Return.h"

using namespace std;

int main() {
    // Kütüphaneyi başlat
    Library library;

    // Yeni Kitaplar oluştur ve ekle
    Book* myNovel = new Novel();
    library.addBook(myNovel);

    Magazine* myMagazine = new Magazine();
    library.addBook(myMagazine);

    HistoryBook* myHistoryBook = new HistoryBook();
    library.addBook(myHistoryBook);

    // Yeni kişiler oluştur ve ekle
    Student* myStudent = new Student();
    library.addPerson(myStudent);

    AcademicStaff* myAcademicStaff = new AcademicStaff();
    library.addPerson(myAcademicStaff);

    // Yeni işlemler oluştur ve ekle
    Borrow* borrowAction = new Borrow();
    library.executeTransaction(borrowAction);

    Return* returnAction = new Return();
    library.executeTransaction(returnAction);

    return 0;
}