#ifndef STUDENT_H
#define STUDENT_H

#include "BasePerson.h"

class Student : public BasePerson {
public:
    Student();
    void displayInfo() const override;
    void setGrade(int grade);
    int getGrade() const;

private:
    int grade;
};

#endif 