#ifndef BASEPERSON_H
#define BASEPERSON_H

#include <string>
using namespace std;

class BasePerson {
public:
    virtual void displayInfo() const = 0;
    virtual string getName() const;

protected:
    string personId;
    string name;
    string email;
};

inline string BasePerson::getName() const {
    return name;
}

#endif