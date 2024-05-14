#include "Student.h"
#include <iostream>

using namespace std;

void Student::displayInfo() const {
    cout << "Öğrenci ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << "\nSınıf: " << grade << endl;
}