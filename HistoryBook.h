#ifndef HISTORYBOOK_H
#define HISTORYBOOK_H

#include "Book.h"

class HistoryBook : public Book {
public:
    void displayInfo() const;
    string getHistoricalPeriod() const { return historicalPeriod; }

private:
    string historicalPeriod;
};

#endif 