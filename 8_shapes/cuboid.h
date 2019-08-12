#ifndef CUBOID_H
#define CUBOID_H

#include "shape.h"
#include <iostream>

/*
Derived class for a cuboid, member data the three lengths
*/

class Cuboid : public Shape
{
protected:
    double height_, width_, depth_;
public:
    Cuboid();
    Cuboid(const double&, const double&, const double&);
    ~Cuboid(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif