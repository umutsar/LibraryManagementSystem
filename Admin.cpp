#include "Admin.h"
#include <iostream>

using namespace std;

void Admin::displayInfo() const {
    cout << "Admin ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << endl;
}