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
#include <sstream> 

using namespace std;

class Database
{
private:
    sqlite3 *db;
    int rc;
    char *errMsg;

    string getCurrentDate();
    string generateUserID();

public:
    Database();
    ~Database();
    void addMember(string name, string surname, string password, string category);
    vector<string> getMember(string userID);
    
    void addBook(string title, string author, string isbn, string genre, string issueNo, string historicalPeriod, string publicationDate, bool isAvailable);
    vector<string> getBookInfo(string isbn);
    bool verifyUser(const string& userId, const string& password);

    vector<vector<string>> listAvailableBooks();
    void updateBookAvailability(string isbn, bool isAvailable);

    bool isUserAdmin(const string& userId);
};

#endif 