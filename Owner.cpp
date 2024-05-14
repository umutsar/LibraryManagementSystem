#include "Owner.h"
#include <iostream>

using namespace std;

void Owner::displayInfo() const {
    cout << "Sahip ID: " << personId << "\nİsim: " << name << "\nEmail: " << email << endl;
}