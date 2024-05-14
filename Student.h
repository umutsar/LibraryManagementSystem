#ifndef STUDENT_H
#define STUDENT_H

#include "BasePerson.h"

class Student : public BasePerson {
public:
    void displayInfo() const override;

private:
    int grade;
};

#endif // STUDENT_H