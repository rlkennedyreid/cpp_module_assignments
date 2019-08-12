#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "shape.h"
#include <iostream>
#include <cmath>
/*
Derived class for an ellipse, member data the two axes of an ellipse
*/
class Ellipse : public Shape
{
protected:
    double minor_axis_, major_axis_;
public:
    Ellipse();
    Ellipse(const double&, const double&);
    ~Ellipse(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif