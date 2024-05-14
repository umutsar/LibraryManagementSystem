#include "Novel.h"
#include <iostream>

using namespace std;

void Novel::displayInfo() const {
    cout << "Roman Adı: " << title << "\nYazar: " << author << "\nISBN: " << isbn << "\nTür: " << genre << endl;
}