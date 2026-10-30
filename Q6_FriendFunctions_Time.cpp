#include <iostream>
using namespace std;

class Time {
    int h, m;

public:
    Time(int hh, int mm) : h(hh), m(mm) {}

    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b) {
    int first = a.h * 60 + a.m;
    int second = b.h * 60 + b.m;

    return (first > second) ? first - second : second - first;
}

bool earlier(const Time& a, const Time& b) {
    if (a.h != b.h) {
        return a.h < b.h;
    }
    return a.m < b.m;
}

int main() {
    Time departure(9, 45), arrival(13, 10);
    cout << minutesBetween(departure, arrival) << ' '
         << boolalpha << earlier(arrival, departure) << '\n';

    Time beforeNoon(11, 55), afterNoon(12, 5);
    cout << minutesBetween(beforeNoon, afterNoon) << ' '
         << earlier(beforeNoon, afterNoon) << '\n';

    Time sameA(10, 30), sameB(10, 30);
    cout << minutesBetween(sameA, sameB) << ' '
         << earlier(sameA, sameB) << '\n';

    return 0;
}