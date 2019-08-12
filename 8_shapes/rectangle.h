#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"
#include <iostream>

/*
Derived class for a rectangle, member data the two lengths
*/

class Rectangle : public Shape
{
protected:
    double height_, width_;
public:
    Rectangle();
    Rectangle(const double&, const double&);
    ~Rectangle(){};
     
     double GetArea() const;
     double GetVolume() const;
     std::string PrintType() const;

};

#endif