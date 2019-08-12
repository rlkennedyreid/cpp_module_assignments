#ifndef SQUARE_H
#define SQUARE_H

#include "rectangle.h"
#include <iostream>

/*
Derived class for a circle, implemented as specialisation of rectangle class
*/

class Square : public Rectangle
{
public:
    Square();
    Square(const double&);
    ~Square(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif