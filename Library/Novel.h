#ifndef NOVEL_H
#define NOVEL_H

#include "Book.h"

class Novel : public Book {
public:
    void displayInfo() const;

private:
    string genre;
};

#endif // NOVEL_H