#ifndef BASEPERSON_H
#define BASEPERSON_H

#include <string>

using namespace std;

class BasePerson {
public:
    virtual void displayInfo() const = 0;

protected:
    string personId;
    string name;
    string email;
};

#endif // BASEPERSON_H