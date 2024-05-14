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
#include "Database.h" // Ekleme

using namespace std;

bool isLogedIn = false;

void showMenu()
{
    cout << "**Yapmak istediginiz islemi girin:" << endl;
    cout << "1- Kitap ekle" << endl;
    cout << "2- Kullanıcı ekle" << endl;
    cout << "3- Kitap ödünç al" << endl;
    cout << "4- Kitap iade et" << endl;
    cout << "5- Çıkış" << endl;
}

void addBook(Library &library, Database &db)
{
    string title, author, isbn, genre, issueNo, historicalPeriod, publicationDate;
    cout << "Kitabin basligi: ";
    cin.ignore();
    getline(cin, title);
    cout << "Kitabin yazari: ";
    getline(cin, author);
    cout << "Kitabin ISBN: ";
    getline(cin, isbn);

    int type;
    cout << "Kitap türünü seçin (1- Roman, 2- Dergi, 3- Tarih Kitabi): ";
    cin >> type;

    Book *book = nullptr;
    switch (type)
    {
    case 1:
        cout << "Roman türü: ";
        cin.ignore();
        getline(cin, genre);
        book = new Novel();
        break;
    case 2:
        cout << "Dergi sayısı: ";
        cin.ignore();
        getline(cin, issueNo);
        book = new Magazine();
        break;
    case 3:
        cout << "Tarih dönemi: ";
        cin.ignore();
        getline(cin, historicalPeriod);
        book = new HistoryBook();
        break;
    default:
        cout << "Geçersiz tür." << endl;
        return;
    }

    cout << "Yayın tarihi (YYYY-MM-DD): ";
    getline(cin, publicationDate);

    library.addBook(book);
    db.addBook(title, author, isbn, genre, issueNo, historicalPeriod, publicationDate, true);
    cout << "Kitap başarıyla eklendi." << endl;
}

void addUser(Library &library, Database &db)
{
    string name, surname, password, category;
    cout << "Kullanıcının adı: ";
    cin.ignore();
    getline(cin, name);
    cout << "Kullanıcının soyadı: ";
    getline(cin, surname);
    cout << "Şifre: ";
    getline(cin, password);
    cout << "Kategori (Student/AcademicStaff): ";
    getline(cin, category);

    BasePerson *person = nullptr;
    if (category == "Student")
    {
        person = new Student();
    }
    else if (category == "AcademicStaff")
    {
        person = new AcademicStaff();
    }
    else
    {
        cout << "Geçersiz kategori." << endl;
        return;
    }

    library.addPerson(person);
    db.addMember(name, surname, password, category);
    cout << "Kullanıcı başarıyla eklendi." << endl;
}

void borrowBook(Library &library)
{
    // Kitap ödünç alma işlemleri
    Borrow *borrowAction = new Borrow();
    library.executeTransaction(borrowAction);
    cout << "Kitap başarıyla ödünç alındı." << endl;
}

void returnBook(Library &library, Database &db)
{
    cout << "İade etmek istediğiniz kitabın ISBN numarasını girin: ";
    string isbn;
    cin >> isbn;

    // Veritabanındaki kitabın durumunu güncelle
    db.updateBookAvailability(isbn, true);

    // İşlemi gerçekleştir
    Return *returnAction = new Return();
    library.executeTransaction(returnAction);

    cout << "Kitap başarıyla iade edildi." << endl;
}

int main()
{
    Library library;
    Database db;

    while (1)
    {
        cout << "LOGIN THE SYSTEM" << endl;

        while (true)
        {
            cout << "user id: ";
            string userId = "";
            cin >> userId;
            cout << "password: ";
            string password = "";
            cin >> password;

            if (!db.verifyUser(userId, password))
            {
                cout << "Invalid credentials, try again." << endl;
            }
            else
            {
                isLogedIn = true;
                cout << "Login Successful!" << endl;
                break;
            }
        }

        if (isLogedIn)
        {
            int choice;
            do
            {
                showMenu();
                cout << "Seçiminiz: ";
                cin >> choice;

                switch (choice)
                {
                case 1:
                    addBook(library, db);
                    break;
                case 2:
                    addUser(library, db);
                    break;
                case 3:
                    borrowBook(library);
                    break;
                case 4:
                    returnBook(library, db);
                    break;
                case 5:
                    cout << "Çıkış yapılıyor..." << endl;
                    break;
                default:
                    cout << "Geçersiz seçim, tekrar deneyin." << endl;
                }
            } while (choice != 5);
        }
    }

    return 0;
}