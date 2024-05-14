#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <string>
#include "Book.h"
#include "BasePerson.h"

using namespace std;

class Librarian {
public:
    void manageBooks(Book* book);
    void managePersons(BasePerson* person);

private:
    string librarianId;
};

#endif // LIBRARIAN_H