#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include "Book.h"
#include "BasePerson.h"
#include "Transaction.h"
#include "Database.h"

using namespace std;

class Library {
public:
    Library();
    void addBook(Book* book);
    void addPerson(BasePerson* person);
    void executeTransaction(Transaction* t);

private:
    vector<Book*> books;
    vector<BasePerson*> persons;
    vector<Transaction*> transactions;
    Database db;
};

#endif 