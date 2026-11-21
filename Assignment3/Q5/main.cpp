#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

class Time
{
    int seconds;

public:
    Time(int h = 0, int m = 0, int s = 0) : seconds(h * 3600 + m * 60 + s) {}

    Time& operator++() { ++seconds; return *this; }

    Time operator++(int)
    {
        Time old = *this;
        ++seconds;
        return old;
    }

    bool operator==(const Time& other) const { return seconds == other.seconds; }
    bool operator<(const Time& other) const { return seconds < other.seconds; }

    void display() const
    {
        cout << seconds / 3600 << ':' << (seconds % 3600) / 60
             << ':' << seconds % 60 << '\n';
    }
};

class Playlist
{
    string* tracks;
    int size;

public:
    Playlist(string names[], int n) : tracks(new string[n]), size(n)
    {
        for (int i = 0; i < size; i++) tracks[i] = names[i];
    }

    string& operator[](int i)
    {
        if (i < 0 || i >= size) throw out_of_range("Track index is out of range");
        return tracks[i];
    }

    const string& operator[](int i) const
    {
        if (i < 0 || i >= size) throw out_of_range("Track index is out of range");
        return tracks[i];
    }

    ~Playlist() { delete[] tracks; }
};

int main()
{
    Time t(0, 0, 5);
    Time a = t++;
    Time b = ++t;
    cout << "Postfix: "; a.display();
    cout << "Prefix: "; b.display();

    string songs[] = {"Song One", "Song Two", "Song Three"};
    Playlist playlist(songs, 3);
    cout << playlist[0] << '\n';

    try { cout << playlist[3] << '\n'; }
    catch (const out_of_range& error) { cout << error.what() << '\n'; }
    return 0;
}
