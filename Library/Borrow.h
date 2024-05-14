#ifndef BORROW_H
#define BORROW_H

#include "Transaction.h"

class Borrow : public Transaction {
public:
    void execute() override;

private:
    string borrowDate;
};

#endif // BORROW_H