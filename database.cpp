#include <iostream>
#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class Database
{
private:
    sqlite3 *db;
    int rc;
    char *errMsg;

    string getCurrentDate()
    {
        time_t now = time(nullptr);
        tm *tm_now = localtime(&now);
        stringstream ss;
        ss << put_time(tm_now, "%Y-%m-%d");
        return ss.str();
    }

public:
    Database()
    {
        rc = sqlite3_open("database.db", &db);
        if (rc)
        {
            cerr << "Veritabanı oluşturulamadı: " << sqlite3_errmsg(db) << endl;
            exit(1);
        }
        else
        {
            cout << "Veritabanı başarıyla oluşturuldu." << endl;
        }
    }

    void addMember(string name, string surname, string category)
    {
        string loginDate = getCurrentDate();
        string insertDataSQL = "INSERT INTO members (name, surname, category, loginDate) VALUES ('" + name + "', '" + surname + "', '" + category + "', '" + loginDate + "');";
        
        rc = sqlite3_exec(db, insertDataSQL.c_str(), NULL, 0, &errMsg);
        if (rc != SQLITE_OK)
        {
            cerr << "Veri eklenemedi: " << errMsg << endl;
            sqlite3_free(errMsg);
        }
        else
        {
            cout << "Veri başarıyla eklendi." << endl;
        }
    }

    ~Database()
    {
        sqlite3_close(db);
    }
};

int main()
{
    Database libraryDatabase;

    libraryDatabase.addMember("Fatih", "Terim", "Coach");

    return 0;
}
