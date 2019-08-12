#ifndef ELLIPSOID_H
#define ELLIPSOID_H

#include "shape.h"
#include <iostream>

/*
Derived class for an ellipsoid, member data the three axes of an ellipsoid
*/

class Ellipsoid : public Shape
{
protected:
    double a_, b_, c_;
public:
    Ellipsoid();
    Ellipsoid(const double&, const double&, const double&);
    ~Ellipsoid(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif