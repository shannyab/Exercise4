#ifndef COMPLEX_HPP
#define COMPLEX_HPP
#include <iostream>

class Complex {
private:
    double real;
    double imag;

public:
//constractor
    Complex(double real = 0.0, double imag = 0.0);
    //get part real 
    double get_real() const;
    //get image
    double get_imag() const;
    //operator
    bool operator==(const Complex& other) const;
    bool operator>(const Complex& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};

#endif 
