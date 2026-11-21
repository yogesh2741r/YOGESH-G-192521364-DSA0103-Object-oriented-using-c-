#include <cstring>
#include <iostream>
using namespace std;

class Text
{
    char* data;

public:
    Text(const char* message = "")
    {
        data = new char[strlen(message) + 1];
        strcpy(data, message);
    }

    Text(const Text& other)
    {
        data = new char[strlen(other.data) + 1];
        strcpy(data, other.data);
    }

    Text& operator=(const Text& other)
    {
        if (this != &other)
        {
            char* copy = new char[strlen(other.data) + 1];
            strcpy(copy, other.data);
            delete[] data;
            data = copy;
        }
        return *this;
    }

    Text operator+(const Text& other) const
    {
        int length = strlen(data) + strlen(other.data);
        char* combined = new char[length + 1];
        strcpy(combined, data);
        strcat(combined, other.data);
        Text result(combined);
        delete[] combined;
        return result;
    }

    bool operator==(const Text& other) const { return strcmp(data, other.data) == 0; }
    bool operator!=(const Text& other) const { return !(*this == other); }

    friend ostream& operator<<(ostream& out, const Text& value)
    {
        out << value.data;
        return out;
    }

    ~Text() { delete[] data; }
};

int main()
{
    Text first("Hello "), second("World");
    Text message = first + second;
    cout << message << '\n';

    Text copy = message;
    cout << boolalpha << (copy == message) << '\n';
    copy = Text("New message");
    copy = copy;
    cout << copy << '\n';
    return 0;
}
