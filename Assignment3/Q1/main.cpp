#include <iostream>
#include <string>
using namespace std;

class Book
{
    string title, author;
    int copies;

public:
    Book() : Book("Not given", "Not given", 0) {}
    Book(string t) : Book(t, "Not given", 1) {}

    Book(string t, string a, int c)
        : title(t), author(a), copies(c < 0 ? 0 : c) {}

    void display() const
    {
        cout << title << " | " << author << " | copies: " << copies << '\n';
    }
};

int main()
{
    Book emptyBook;
    Book donatedBook("The Alchemist");
    Book fullBook("Wings of Fire", "A.P.J. Abdul Kalam", 5);
    Book invalidBook("Unknown", "Unknown", -3);

    emptyBook.display();
    donatedBook.display();
    fullBook.display();
    invalidBook.display();
    return 0;
}
