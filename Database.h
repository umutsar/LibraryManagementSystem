#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <ctime>
#include <iomanip>
#include <random>
#include <vector>

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

    string generateUserID()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 9);

        string userID = "";
        for (int i = 0; i < 8; ++i)
        {
            userID += to_string(dis(gen));
        }
        return userID;
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

    void addMember(string name, string surname, string password, string category)
    {
        string loginDate = getCurrentDate();
        string insertDataSQL = "INSERT INTO members (userID, name, surname, password, category, loginDate) VALUES ('" + generateUserID() + "', '" + name + "', '" + surname + "', '" + password + "', '" + category + "', '" + loginDate + "');";

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

    vector<string> getMember(string userID)
    {
        string selectDataSQL = "SELECT * FROM members WHERE userID = '" + userID + "';";
        sqlite3_stmt *stmt;
        rc = sqlite3_prepare_v2(db, selectDataSQL.c_str(), -1, &stmt, nullptr);
        if (rc != SQLITE_OK)
        {
            cerr << "Sorgu hazırlanamadı: " << sqlite3_errmsg(db) << endl;
            return {"Hata: Sorgu hazırlanamadı."};
        }

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW)
        {
            vector<string> memberData;
            for (int i = 0; i < sqlite3_column_count(stmt); ++i)
            {
                memberData.push_back(reinterpret_cast<const char *>(sqlite3_column_text(stmt, i)));
            }
            sqlite3_finalize(stmt);
            return memberData;
        }
        else if (rc == SQLITE_DONE)
        {
            sqlite3_finalize(stmt);
            return {"Hata: Kullanıcı bulunamadı."};
        }
        else
        {
            cerr << "Sorgu çalıştırılamadı: " << sqlite3_errmsg(db) << endl;
            sqlite3_finalize(stmt);
            return {"Hata: Sorgu çalıştırılamadı."};
        }
    }

    ~Database()
    {
        sqlite3_close(db);
    }
};

#endif // DATABASE_H