#include "complex.hpp"
#include <stdexcept>
#include <iomanip> 


Complex::Complex(double re, double im) : real(re), imag(im) {}

//get real
double Complex::get_real() const 
{
    return real;
}

//get image
double Complex::get_imag() const 
{
    return imag;
}

//operator ==
bool Complex::operator==(const Complex& other) const 
{
    return real == other.real && imag == other.imag;
}


//operator >
bool Complex::operator>(const Complex& other) const 
{
    return (real > other.get_real()) || (real == other.get_real() && imag > other.get_imag());
}

//operator <<
std::ostream& operator<<(std::ostream& os, const Complex& c) 
{
    os << std::fixed << std::setprecision(2); 
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}
