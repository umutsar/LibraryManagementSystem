#ifndef RETURN_H
#define RETURN_H

#include "Transaction.h"

class Return : public Transaction {
public:
    void execute() override;

private:
    string returnDate;
};

#endif 