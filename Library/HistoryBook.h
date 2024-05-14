#ifndef HISTORYBOOK_H
#define HISTORYBOOK_H

#include "Book.h"

class HistoryBook : public Book {
public:
    void displayInfo() const;

private:
    string historicalPeriod;
};

#endif // HISTORYBOOK_H