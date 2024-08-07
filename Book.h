#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
    void checkout();
    void returnBook();

    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    string getISBN() const { return isbn; }

protected:
    string title;
    string author;
    string isbn;
};

#endif