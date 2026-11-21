#include <iostream>
using namespace std;

class Event
{
    int rows, seatsPerRow, booked;
    char** seats;

public:
    Event(int r, int s) : rows(r), seatsPerRow(s), booked(0), seats(nullptr)
    {
        if (rows <= 0 || seatsPerRow <= 0)
        {
            rows = 0;
            seatsPerRow = 0;
            cout << "Event has no seats\n";
            return;
        }

        seats = new char*[rows];
        for (int i = 0; i < rows; i++)
        {
            seats[i] = new char[seatsPerRow];
            for (int j = 0; j < seatsPerRow; j++) seats[i][j] = 'O';
        }
        cout << "Event created\n";
    }

    bool bookSeat(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow) return false;
        if (seats[r][s] == 'X') return false;
        seats[r][s] = 'X';
        booked++;
        return true;
    }

    bool cancelSeat(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow) return false;
        if (seats[r][s] == 'O') return false;
        seats[r][s] = 'O';
        booked--;
        return true;
    }

    void display() const
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < seatsPerRow; j++) cout << seats[i][j] << ' ';
            cout << '\n';
        }
    }

    ~Event()
    {
        for (int i = 0; i < rows; i++) delete[] seats[i];
        delete[] seats;
        cout << "Event closed. Booked seats: " << booked << '\n';
    }
};

int main()
{
    Event collegeEvent(3, 4);
    collegeEvent.bookSeat(0, 1);
    collegeEvent.bookSeat(2, 3);
    collegeEvent.cancelSeat(0, 1);
    collegeEvent.display();

    {
        Event smallEvent(2, 2);
        smallEvent.bookSeat(1, 1);
    }

    Event* specialEvent = new Event(1, 3);
    specialEvent->bookSeat(0, 0);
    delete specialEvent;
    return 0;
}
