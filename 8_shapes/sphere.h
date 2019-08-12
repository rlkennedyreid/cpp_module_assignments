#ifndef SPHERE_H
#define SPHERE_H

#include "ellipsoid.h"
#include <iostream>

/*
Derived class for a sphere, implemented as specialisation of ellipsoid class
*/

class Sphere : public Ellipsoid
{
public:
    Sphere();
    Sphere(const double&);
    ~Sphere(){};

    double GetArea() const;
    double GetVolume() const;
    std::string PrintType() const;

};

#endif