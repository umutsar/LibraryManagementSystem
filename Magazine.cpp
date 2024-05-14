#include "Magazine.h"
#include <iostream>

using namespace std;

void Magazine::displayInfo() const {
    cout << "Dergi Adı: " << title << "\nYazar: " << author << "\nISBN: " << isbn << "\nSayı No: " << issueNo << endl;
}