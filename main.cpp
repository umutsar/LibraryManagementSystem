#include <iostream>
#include <string>
#include <sqlite3.h>


using namespace std;

class Item {
protected:
    string title;
    string author;
    string ISBN;
    bool onLoan;

public:
    Item(string title, string author, string ISBN)
        : title(title), author(author), ISBN(ISBN), onLoan(false) {}

    virtual void checkout() = 0;
    virtual void returnItem() = 0;

    virtual void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << ISBN << endl;
        cout << "On Loan: " << (onLoan ? "Yes" : "No") << endl;
    }
};

class Book : public Item {
private:
    int pageCount;
    string genre;

public:
    Book(string title, string author, string ISBN, int pageCount, string genre)
        : Item(title, author, ISBN), pageCount(pageCount), genre(genre) {}

    void checkout() override {
        if (!onLoan) {
            cout << "Book checked out successfully!" << endl;
            onLoan = true;
        } else {
            cout << "Book is already on loan." << endl;
        }
    }

    void returnItem() override {
        if (onLoan) {
            cout << "Book returned successfully!" << endl;
            onLoan = false;
        } else {
            cout << "Book is not on loan." << endl;
        }
    }

    void display() override {
        cout << "----- Book Details -----" << endl;
        Item::display(); // Call base class's display method
        cout << "Page Count: " << pageCount << endl;
        cout << "Genre: " << genre << endl;
    }
};

class Magazine : public Item {
private:
    int issueNumber;
    string genre;

public:
    Magazine(string title, string author, string ISBN, int issueNumber, string genre)
        : Item(title, author, ISBN), issueNumber(issueNumber), genre(genre) {}

    void checkout() override {
    }

    void returnItem() override {
    }

    void display() override {
    }
};

class DVD : public Item {
private:
    int duration;
    string genre;

public:
    DVD(string title, string author, string ISBN, int duration, string genre)
        : Item(title, author, ISBN), duration(duration), genre(genre) {}

    void checkout() override {
    }

    void returnItem() override {
    }

    void display() override {
    }
};

int main() {
    return 0;
}
