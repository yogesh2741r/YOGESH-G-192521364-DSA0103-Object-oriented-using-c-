#include <iostream>
#include <string>
using namespace std;

class Prescription
{
    int count;
    string* medicines;

public:
    Prescription(int n) : count(n), medicines(new string[n]) {}

    Prescription(const Prescription& other)
        : count(other.count), medicines(new string[other.count])
    {
        for (int i = 0; i < count; i++)
            medicines[i] = other.medicines[i];
    }

    Prescription& operator=(const Prescription& other)
    {
        if (this != &other)
        {
            string* copy = new string[other.count];
            for (int i = 0; i < other.count; i++)
                copy[i] = other.medicines[i];

            delete[] medicines;
            medicines = copy;
            count = other.count;
        }
        return *this;
    }

    ~Prescription() { delete[] medicines; }

    void set(int i, string name)
    {
        if (i >= 0 && i < count) medicines[i] = name;
    }

    string get(int i) const
    {
        if (i >= 0 && i < count) return medicines[i];
        return "";
    }
};

int main()
{
    Prescription p(2);
    p.set(0, "Paracetamol");
    p.set(1, "ORS");

    Prescription q = p;
    q.set(1, "Cetirizine");

    Prescription r(1);
    r = p;
    p.set(0, "Ibuprofen");

    cout << p.get(0) << ' ' << p.get(1) << " | "
         << q.get(0) << ' ' << q.get(1) << " | "
         << r.get(0) << ' ' << r.get(1) << '\n';
    return 0;
}
