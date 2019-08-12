#ifndef CIRCLE_H
#define CIRCLE_H

#include "ellipse.h"
#include <iostream>

/*
Derived class for a circle, implemented as specialisation of ellipse class
*/

class Circle : public Ellipse
{
public:
    Circle();
    Circle(const double&);
    ~Circle(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif