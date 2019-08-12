#define _USE_MATH_DEFINES

#include "circle.h"

// Printing messages in constructors for demonstration
Circle::Circle() : Ellipse() {
    std::cout << "Circle: Default constructor called" << std::endl;
}

Circle::Circle(const double& radius) : Ellipse(radius, radius) {
    std::cout << "Circle: Parameterised constructor called" << std::endl;
}

double Circle::GetArea() const{
    return M_PI * minor_axis_ * major_axis_;
}

double Circle::GetVolume() const{
    return .0; //2D
}

std::string Circle::PrintType() const{
    return "Circle";
}