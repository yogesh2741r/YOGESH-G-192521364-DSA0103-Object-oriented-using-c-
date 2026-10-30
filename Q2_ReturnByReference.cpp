#include <iostream>
using namespace std;

int& highest(int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) {
        if (marks[i] > marks[best]) {
            best = i;
        }
    }
    return marks[best];
}

// This intentionally unsafe function is kept commented out.
// Uncomment it separately to observe the compiler warning.
// int& unsafe() {
//     int local = 10;
//     return local; // Returning a reference to a local variable is invalid.
// }

int main() {
    int marks[] = {78, 91, 84};

    highest(marks, 3) += 2;

    cout << "Updated highest mark: " << highest(marks, 3) << '\n';
    cout << "All marks: ";
    for (int mark : marks) {
        cout << mark << ' ';
    }
    cout << '\n';

    return 0;
}