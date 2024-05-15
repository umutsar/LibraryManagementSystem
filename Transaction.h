#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
using namespace std;

class Transaction {
public:
    virtual void execute() = 0;

protected:
    string transId;
    string date;
};

#endif