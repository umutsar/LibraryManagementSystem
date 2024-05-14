#include "AcademicStaff.h"
#include <iostream>

using namespace std;

void AcademicStaff::displayInfo() const {
    cout << "Akademik Personel ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << "\nBölüm: " << department << endl;
}