#include "Student.h"
#include <iostream>

using namespace std;

Student::Student() : grade(0) {
}

void Student::displayInfo() const {
    cout << "Öğrenci ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << "\nSınıf: " << grade << endl;
}

void Student::setGrade(int grade) {
    this->grade = grade;
}

int Student::getGrade() const {
    return grade;
}