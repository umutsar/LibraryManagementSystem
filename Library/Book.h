#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
    void checkout();
    void returnBook();

protected:
    string title;
    string author;
    string isbn;
};

#endif // BOOK_H