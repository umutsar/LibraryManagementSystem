#include <iostream>
#include "Library.h"
#include "Book.h"
#include "Magazine.h"
#include "Novel.h"
#include "HistoryBook.h"
#include "Student.h"
#include "AcademicStaff.h"
#include "Borrow.h"
#include "Return.h"
#include "Database.h"

using namespace std;

bool isLogedIn = false;
bool isAdmin = false;

void showMenu()
{
    cout << "**Yapmak istediginiz islemi girin:" << endl;
    cout << "1- Kitap ödünç al" << endl;
    cout << "2- Kitap iade et" << endl;
    if (isAdmin)
    {
        cout << "3- Kitap ekle" << endl;
        cout << "4- Kullanıcı ekle" << endl;
    }
    cout << "0- Çıkış" << endl;
}

void addBook(Library &library, Database &db)
{
    string title, author, isbn, genre, issueNo, historicalPeriod, publicationDate;
    cin.ignore(); // \n lerin karmaşıklığını önlemek için.
    cout << "Kitabin basligi: ";
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
        if (title.empty() || author.empty() || isbn.empty() || genre.empty())
        {
            cout << "Gerekli bilgiler eksik. Kitap eklenemedi." << endl;
            return;
        }
        book = new Novel();
        break;
    case 2:
        cout << "Dergi sayısı: ";
        cin.ignore();
        getline(cin, issueNo);
        if (title.empty() || author.empty() || isbn.empty() || issueNo.empty())
        {
            cout << "Gerekli bilgiler eksik. Kitap eklenemedi." << endl;
            return;
        }
        book = new Magazine();
        break;
    case 3:
        cout << "Tarih dönemi: ";
        cin.ignore();
        getline(cin, historicalPeriod);
        if (title.empty() || author.empty() || isbn.empty() || historicalPeriod.empty())
        {
            cout << "Gerekli bilgiler eksik. Kitap eklenemedi." << endl;
            return;
        }
        book = new HistoryBook();
        break;
    default:
        cout << "Geçersiz tür." << endl;
        return;
    }

    cout << "Yayın tarihi (YYYY-MM-DD): ";
    getline(cin, publicationDate);

    if (title.empty() || author.empty() || isbn.empty() || publicationDate.empty())
    {
        cout << "Bazı zorunlu bilgiler eksik, kitap eklenemedi." << endl;
        return;
    }

    library.addBook(book);
    db.addBook(title, author, isbn,
               (type == 1 ? genre : ""),
               (type == 2 ? issueNo : ""),
               (type == 3 ? historicalPeriod : ""),
               publicationDate, 1);
}

void addUser(Library &library, Database &db)
{
    system("clear");

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
    system("clear");

    // Kitap ödünç alma işlemleri
    Borrow *borrowAction = new Borrow();
    library.executeTransaction(borrowAction);
    cout << "Kitap başarıyla ödünç alındı." << endl;
}

void returnBook(Library &library, Database &db)
{
    system("clear");

    cout << "İade etmek istediğiniz kitabın ISBN numarasını girin: ";
    string isbn;
    cin >> isbn;

    // Veritabanındaki kitabın varlığını değiştirdiğimiz yer
    db.updateBookAvailability(isbn, true);

    // İşlemi gerçekleştirdiğimiz yer
    Return *returnAction = new Return();
    library.executeTransaction(returnAction);

    cout << "Kitap başarıyla iade edildi." << endl;
}

int main()
{
    Library library;
    Database db; // Veritabanına bağlanalım diye burdan nesne oluşturuyoz.
    system("clear");

    cout << "LOGIN THE SYSTEM" << endl;

    string userId;
    string password;
    while (true)
    {
        cout << "user id: ";
        cin >> userId;
        cout << "password: ";
        cin >> password;

        system("clear");

        if (!db.verifyUser(userId, password))
        {
            cout << "Invalid credentials, try again." << endl;
        }
        else
        {
            isLogedIn = true;
            isAdmin = db.isUserAdmin(userId);
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
                borrowBook(library);
                break;

            case 2:
                returnBook(library, db);
                break;

            case 3:
                if (isAdmin)
                {
                    addBook(library, db);
                }
                else
                {
                    cout << "Bu işlemi gerçekleştirme yetkiniz yok." << endl;
                }
                break;

            case 4:
                if (isAdmin)
                {
                    addUser(library, db);
                }
                else
                {
                    cout << "Bu işlemi gerçekleştirme yetkiniz yok." << endl;
                }
                break;

            case 0:
                cout << "Çıkış yapılıyor..." << endl;
                isLogedIn = false;
                isAdmin = false; // Çıkış yapıldıktan sonra admin işlemleri olmasın diye false olarak değiştiriyoruz burdaki bayrağı
                break;

            default:
                cout << "Geçersiz seçim, tekrar deneyin." << endl;
            }

        } while (choice != 0);
    }

    return 0;
}