#include "HistoryBook.h"
#include <iostream>

using namespace std;

void HistoryBook::displayInfo() const {
    cout << "Tarih Kitabı Adı: " << title << "\nYazar: " << author << "\nISBN: " << isbn << "\nTarih: " << historicalPeriod << endl;
}