#ifndef NOVEL_H
#define NOVEL_H

#include "Book.h"

class Novel : public Book {
public:
    void displayInfo() const;
    string getGenre() const { return genre; }

private:
    string genre;
};

#endif