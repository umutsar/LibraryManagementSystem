#include "Database.h"
#include <iostream>
#include <sstream> // Ekleme

using namespace std;

Database::Database() {
    rc = sqlite3_open("database.db", &db);
    if (rc) {
        cerr << "Veritabanı oluşturulamadı: " << sqlite3_errmsg(db) << endl;
        exit(1);
    } else {
        cout << "Veritabanı başarıyla oluşturuldu." << endl;
    }
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::addMember(string name, string surname, string password, string category) {
    string loginDate = getCurrentDate();
    string insertDataSQL = "INSERT INTO members (userID, name, surname, password, category, loginDate, isAdmin) VALUES ('" 
                            + generateUserID() + "', '" + name + "', '" + surname + "', '" + password + "', '" 
                            + category + "', '" + loginDate + "', 0);";

    rc = sqlite3_exec(db, insertDataSQL.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Veri eklenemedi: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Veri başarıyla eklendi." << endl;
    }
}

vector<string> Database::getMember(string userID) {
    string selectDataSQL = "SELECT * FROM members WHERE userID = '" + userID + "';";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, selectDataSQL.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
        return {"Hata: Sorgu hazırlanamadı."};
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        vector<string> memberData;
        for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
            memberData.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
        }
        sqlite3_finalize(stmt);
        return memberData;
    } else if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return {"Hata: Kullanıcı bulunamadı."};
    } else {
        cerr << "Sorgu çalıştırılamadı: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return {"Hata: Sorgu çalıştırılamadı."};
    }
}

string Database::getCurrentDate() {
    time_t now = time(nullptr);
    tm *tm_now = localtime(&now);
    stringstream ss;
    ss << put_time(tm_now, "%Y-%m-%d");
    return ss.str();
}

string Database::generateUserID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

    string userID = "";
    for (int i = 0; i < 8; ++i) {
        userID += to_string(dis(gen));
    }
    return userID;
}

void Database::addBook(string title, string author, string isbn, string genre, string issueNo, string historicalPeriod, string publicationDate, bool isAvailable) {
    string insertBookSQL = "INSERT INTO books (title, author, isbn, genre, issueNo, historicalPeriod, publicationDate, isAvailable) VALUES ('"
                            + title + "', '" + author + "', '" + isbn + "', '" + genre + "', '" + issueNo + "', '"
                            + historicalPeriod + "', '" + publicationDate + "', " + (isAvailable ? "1" : "0") + ");";

    rc = sqlite3_exec(db, insertBookSQL.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Kitap eklenemedi: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Kitap başarıyla eklendi." << endl;
    }
}

vector<string> Database::getBookInfo(string isbn) {
    string selectBookSQL = "SELECT * FROM books WHERE isbn = '" + isbn + "';";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, selectBookSQL.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
        return {"Hata: Sorgu hazırlanamadı."};
    }

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        vector<string> bookData;
        for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
            bookData.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
        }
        sqlite3_finalize(stmt);
        return bookData;
    } else if (rc == SQLITE_DONE) {
        sqlite3_finalize(stmt);
        return {"Hata: Kitap bulunamadı."};
    } else {
        cerr << "Sorgu çalıştırılamadı: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return {"Hata: Sorgu çalıştırılamadı."};
    }
}

bool Database::verifyUser(const string& userId, const string& password) {
    string selectUserSQL = "SELECT * FROM members WHERE userID = '" + userId + "' AND password = '" + password + "';";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, selectUserSQL.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    rc = sqlite3_step(stmt);
    bool userExists = rc == SQLITE_ROW;
    sqlite3_finalize(stmt);
    return userExists;
}

vector<vector<string>> Database::listAvailableBooks() {
    string sql = "SELECT title, author, isbn FROM books WHERE isAvailable = 1;";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
        return {};
    }
    
    vector<vector<string>> availableBooks;
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        vector<string> book;
        for (int i = 0; i < sqlite3_column_count(stmt); ++i) {
            book.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
        }
        availableBooks.push_back(book);
    }

    sqlite3_finalize(stmt);
    return availableBooks;
}

void Database::updateBookAvailability(string isbn, bool isAvailable) {
    string sql = "UPDATE books SET isAvailable = " + to_string(isAvailable) + " WHERE isbn = '" + isbn + "';";
    rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "Kitap durumu güncellenemedi: " << errMsg << endl;
        sqlite3_free(errMsg);
    } else {
        cout << "Kitap durumu başarıyla güncellendi." << endl;
    }
}

bool Database::isUserAdmin(const string& userId) {
    string sql = "SELECT isAdmin FROM members WHERE userID = '" + userId + "';";
    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    rc = sqlite3_step(stmt);
    bool isAdmin = false;
    if (rc == SQLITE_ROW) {
        isAdmin = sqlite3_column_int(stmt, 0) == 1;
    }
    sqlite3_finalize(stmt);
    return isAdmin;
}