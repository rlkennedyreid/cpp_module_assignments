#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
#include <string>

/*
ABSTRACT BASE CLASS FOR SHAPES
- Shapes can be 2D or 3D, so pure virtual functions to return areas and volumes are given

- A function that returns a string with shape 'type' is also given (e.g. square, circle...)
*/
class Shape {
public:
    virtual ~Shape(){};

    virtual double GetArea() const = 0;
    virtual double GetVolume() const = 0;
    virtual std::string PrintType() const = 0;

};

#endif