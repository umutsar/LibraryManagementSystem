#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "Book.h"

class Magazine : public Book {
public:
    void displayInfo() const;
    string getIssueNo() const { return issueNo; }

private:
    string issueNo;
};

#endif // MAGAZINE_H