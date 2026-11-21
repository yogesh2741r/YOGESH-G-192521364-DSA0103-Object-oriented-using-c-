#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;

class Complex
{
    double real, imag;

public:
    Complex() : real(0), imag(0) {}
    Complex(double r) : real(r), imag(0) {}
    Complex(double r, double i) : real(r), imag(i) {}

    Complex operator+(const Complex& other) const
    {
        return Complex(real + other.real, imag + other.imag);
    }

    Complex operator-(const Complex& other) const
    {
        return Complex(real - other.real, imag - other.imag);
    }

    Complex operator*(const Complex& other) const
    {
        return Complex(real * other.real - imag * other.imag,
                       real * other.imag + imag * other.real);
    }

    Complex operator/(const Complex& other) const
    {
        double d = other.real * other.real + other.imag * other.imag;
        if (d == 0) throw runtime_error("Cannot divide by zero impedance");

        return Complex((real * other.real + imag * other.imag) / d,
                       (imag * other.real - real * other.imag) / d);
    }

    bool operator==(const Complex& other) const
    {
        return real == other.real && imag == other.imag;
    }

    double magnitude() const { return sqrt(real * real + imag * imag); }

    friend ostream& operator<<(ostream& out, const Complex& value)
    {
        out << value.real;
        if (value.imag >= 0) out << " + j" << value.imag;
        else out << " - j" << -value.imag;
        return out;
    }
};

int main()
{
    try
    {
        Complex resistor(10, 0), inductor(0, 5), capacitor(0, -2);
        Complex series = resistor + inductor + capacitor;
        cout << "Series impedance: " << series << '\n';
        cout << "Magnitude: " << series.magnitude() << '\n';

        Complex z1(10, 2), z2(5, -1);
        cout << "Parallel impedance: " << (z1 * z2) / (z1 + z2) << '\n';

        Complex zero(0, 0);
        cout << z1 / zero << '\n';
    }
    catch (const runtime_error& error) { cout << error.what() << '\n'; }
    return 0;
}
